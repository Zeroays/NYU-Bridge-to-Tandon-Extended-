#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

const int GRID_SIZE = 20;

const int DOODLEBUG_AMT = 5;
const int ANT_AMT = 100;

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int AMT_OF_DIRECTIONS = 4;

const int ANT_BREEDING_TIME = 3;
const int DOODLEBUG_BREEDING_TIME = 8;
const int DOODLEBUG_STARVE_TIME = 3;

const char DOODLEBUG = 'D';
const char ANT = 'o';
const char EMPTY_CELL = '-';

class World;

class Position {
    private:
        int row;
        int col;
    public:
        Position() : row(0), col(0) {};
        Position(int row, int col) : row(row), col(col) {};
        ~Position() {}
        int get_row() const { return row; };
        int get_col() const { return col; };
        void set_row(const int& r) { row = r; }
        void set_col(const int& c) { col = c; }
};



class Organism {
    private:
        Position pos;
    protected:
        char type;
        int breed_timer;
    public:
        Organism() { pos = Position(); breed_timer = 0; }
        Organism(const Position& p) { pos = p; breed_timer = 0; }
        virtual ~Organism() {};
        Position get_pos() const { return pos; }
        void set_pos(const Position& p); 
        char get_type() const { return type; }
        virtual void move(World& world) = 0;
        virtual void breed(World& world) = 0;
        virtual void die(World& world) = 0;
        friend ostream& operator<<(ostream& output, const Organism& organism);
};

class World {
    private:
        void nullify_grid();
        void assign_organisms_on_grid();
        void select_position_for_organism(int row, int col, char organism_type);
        vector<Organism*> find_target_organism(const char& type);
        bool is_cell_within_bounds(const Position& pos);
        Organism* grid[GRID_SIZE][GRID_SIZE];
    public:
        World();
        ~World();
        void draw() const;
        void update();
        bool is_cell_available(const Position& pos);
        vector<Position> get_available_adjacent_cells(const Position& pos);
        vector<Position> get_adjacent_ants(const Position& pos);
        Organism* get_organism(const Position& pos) const;
        void move_organism(Organism* organism, const Position& new_pos);
        void set_organism(Organism* organism, const Position& pos);
        void delete_organism(Organism* organism);
};

void Organism::set_pos(const Position& p) {
    pos.set_col(p.get_col());
    pos.set_row(p.get_row());
}

ostream& operator<<(ostream& output, const Organism& organism) {
    cout << organism.get_type() << " ";

    return output;
}

class Ant : public Organism {
    public:
        Ant(): Organism() { type = ANT; }
        Ant(const Position& pos) :Organism(pos) { type = ANT; }
        virtual ~Ant() {};
        void move(World& world);
        void breed(World& world);
        virtual void die(World& world) { world.delete_organism(this); }
};

void Ant::move(World& world) {
    int rnd_direction = rand() % AMT_OF_DIRECTIONS;
    Position cur_pos = get_pos();
    Position new_pos = cur_pos;

    switch (rnd_direction) {
        case UP:
            new_pos.set_row(cur_pos.get_row() - 1);
            break;
        case DOWN:
            new_pos.set_row(cur_pos.get_row() + 1);
            break;
        case LEFT:
            new_pos.set_col(cur_pos.get_col() - 1);
            break;
        case RIGHT:
            new_pos.set_col(cur_pos.get_col() + 1);
            break;
        default:
            break;
    }

    if (world.is_cell_available(new_pos)) {
        world.move_organism(this, new_pos);
    }
    breed_timer++;
}

void Ant::breed(World& world) {
    if (breed_timer < ANT_BREEDING_TIME) {
        return ;
    }
    Position cur_pos = get_pos();

    vector<Position> empty_cells = world.get_available_adjacent_cells(cur_pos);
    int amt_of_empty_cells = empty_cells.size();

    if (amt_of_empty_cells > 0) {
        int rnd_cell_num = rand() % amt_of_empty_cells;
        Position chosen_cell = empty_cells[rnd_cell_num];

        world.set_organism(new Ant(), chosen_cell);
    }
    
    breed_timer = 0;
}

class Doodlebug : public Organism {
    public:
        Doodlebug(): Organism() { type = DOODLEBUG; starve_timer = 0; }
        Doodlebug(const Position& pos) :Organism(pos) { type = DOODLEBUG; starve_timer = 0; }
        virtual ~Doodlebug() {};
        void move(World& world);
        void breed(World& world);
        void die(World& world);
    private:
        int starve_timer;

};

void Doodlebug::move(World& world) {
    Position cur_pos = get_pos();
    vector<Position> adjacent_ants = world.get_adjacent_ants(cur_pos);

    int amt_of_adjacent_ants = adjacent_ants.size();
    if (amt_of_adjacent_ants == 0) {
        Position new_pos = cur_pos;
        int rnd_direction = rand() % AMT_OF_DIRECTIONS;

        switch (rnd_direction) {
            case UP:
                new_pos.set_row(cur_pos.get_row() - 1);
                break;
            case DOWN:
                new_pos.set_row(cur_pos.get_row() + 1);
                break;
            case LEFT:
                new_pos.set_col(cur_pos.get_col() - 1);
                break;
            case RIGHT:
                new_pos.set_col(cur_pos.get_col() + 1);
                break;
            default:
                break;
        }

        if (world.is_cell_available(new_pos)) {
            world.move_organism(this, new_pos);
        }

        breed_timer++;
        starve_timer++;
    } else {
        int rnd_ant_cell_num = rand() % amt_of_adjacent_ants;
        Position rnd_ant_pos = adjacent_ants[rnd_ant_cell_num];

        Organism* ant = world.get_organism(rnd_ant_pos);
        ant->die(world);
        world.move_organism(this, ant->get_pos());

        breed_timer++;
        starve_timer = 0;
    }
   
}

void Doodlebug::breed(World& world) {
    if (breed_timer < DOODLEBUG_BREEDING_TIME) {
        return ;
    }
    Position cur_pos = get_pos();

    vector<Position> empty_cells = world.get_available_adjacent_cells(cur_pos);
    int amt_of_empty_cells = empty_cells.size();

    if (amt_of_empty_cells > 0) {
        int rnd_cell_num = rand() % amt_of_empty_cells;
        Position chosen_cell = empty_cells[rnd_cell_num];

        world.set_organism(new Doodlebug(), chosen_cell);
    }
    
    breed_timer = 0;
}

void Doodlebug::die(World& world) {
    if (starve_timer < DOODLEBUG_STARVE_TIME) {
        return ;
    }
    world.delete_organism(this);
}



vector<Organism*> World::find_target_organism(const char& type) {
    vector<Organism*> organisms;

    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {

            Organism* organism = grid[row][col];
            if (organism != nullptr && organism->get_type() == type) {
                organisms.push_back(organism);
            }

        }
    }

    return organisms;
}

void World::draw() const {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] == nullptr) {
                cout << EMPTY_CELL << " ";
            } else {
                cout << *grid[row][col];
            }
        }
        cout << endl;
    }
    cout << endl;
}

void World::update() {
    vector<Organism*> ants;
    vector<Organism*> doodlebugs;

    doodlebugs = find_target_organism(DOODLEBUG);

    for (int i = 0; i < doodlebugs.size(); i++) {
        doodlebugs[i]->move(*this);
    }

    ants = find_target_organism(ANT);

    for (int i = 0; i < ants.size(); i++) {
        ants[i]->move(*this);
    }

    for (int i = 0; i < doodlebugs.size(); i++) {
        doodlebugs[i]->breed(*this);
    }

    for (int i = 0; i < ants.size(); i++) {
        ants[i]->breed(*this);
    }

    for (int i = 0; i < doodlebugs.size(); i++) {
        doodlebugs[i]->die(*this);
    }
}

bool World::is_cell_within_bounds(const Position& pos) {
    int row = pos.get_row(), col = pos.get_col();
    return (row >= 0) && (row < GRID_SIZE) && (col >= 0) && (col < GRID_SIZE);
}

bool World::is_cell_available(const Position& pos) {
    int row = pos.get_row(), col = pos.get_col();
    return  is_cell_within_bounds(pos) && (grid[row][col] == nullptr);
}

vector<Position> World::get_available_adjacent_cells(const Position& pos) {
    vector<Position> available_cells;

    Position up_cell = Position(pos.get_row() - 1, pos.get_col());
    Position down_cell = Position(pos.get_row() + 1, pos.get_col());
    Position left_cell = Position(pos.get_row(), pos.get_col() - 1); 
    Position right_cell = Position(pos.get_row(), pos.get_col() + 1);
    vector<Position> possible_cells = { up_cell, down_cell, left_cell, right_cell };

    for (int i = 0; i < possible_cells.size(); i++) {

        Position pos = possible_cells[i];
        if (is_cell_available(pos)) {
            available_cells.push_back(pos);
        }

    }

    return available_cells;
}

vector<Position> World::get_adjacent_ants(const Position& pos) {
    vector<Position> ants;

    Position up_cell = Position(pos.get_row() - 1, pos.get_col());
    Position down_cell = Position(pos.get_row() + 1, pos.get_col());
    Position left_cell = Position(pos.get_row(), pos.get_col() - 1); 
    Position right_cell = Position(pos.get_row(), pos.get_col() + 1);
    vector<Position> possible_cells = { up_cell, down_cell, left_cell, right_cell };

    for (int i = 0; i < possible_cells.size(); i++) {

        Position pos = possible_cells[i];
        int row = pos.get_row(), col = pos.get_col();
        if (is_cell_within_bounds(pos) && grid[row][col] != nullptr && grid[row][col]->get_type() == ANT) {
            ants.push_back(pos);
        }

    }

    return ants;
}

Organism* World::get_organism(const Position& pos) const {
    int row = pos.get_row(), col = pos.get_col();
    return grid[row][col];
}

void World::move_organism(Organism* organism, const Position& new_pos) {
    Position cur_pos = organism->get_pos();

    grid[new_pos.get_row()][new_pos.get_col()] = organism;
    grid[new_pos.get_row()][new_pos.get_col()]->set_pos(new_pos);
    grid[cur_pos.get_row()][cur_pos.get_col()] = nullptr;
}

void World::nullify_grid() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = nullptr;
        }
    }
}

void World::set_organism(Organism* organism, const Position& pos) {
    int row = pos.get_row(), col = pos.get_col();

    organism->set_pos(pos);
    grid[row][col] = organism;
}

void World::delete_organism(Organism* organism) {
    Position pos = organism->get_pos();

    grid[pos.get_row()][pos.get_col()] = nullptr;
    delete organism;
}

void World::assign_organisms_on_grid() {
    for (int i = 0; i < DOODLEBUG_AMT; i++) {
        int row = rand() % GRID_SIZE, col = rand() % GRID_SIZE;
        select_position_for_organism(row, col, DOODLEBUG);
    }
    for (int i = 0; i < ANT_AMT; i++) {
        int row = rand() % GRID_SIZE, col = rand() % GRID_SIZE;
        select_position_for_organism(row, col, ANT);
    }
}

void World::select_position_for_organism(int row, int col, char organism_type) {
    while (grid[row][col] != nullptr) {
        row = rand() % GRID_SIZE, col = rand() % GRID_SIZE;
    }
    switch (organism_type) {
        case ANT:
            grid[row][col] = new Ant(Position(row, col));
            break;
        case DOODLEBUG:
            grid[row][col] = new Doodlebug(Position(row, col));
            break;
        default:
            grid[row][col] = nullptr;
            break;
    }
}

World::World() {
    nullify_grid();
    assign_organisms_on_grid();
}

World::~World() {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            delete grid[row][col];
        }
    }
}

int main() {
    srand(time(0));

    int cycles = 0;
    World w = World();
    
    while (true) {
        cout << "Drawing World on Cycle " << cycles << endl;
        w.draw();

        cout << "Please press ENTER to continue...";
        cin.get();

        w.update();
        cycles++;
    }

    return 0;
}