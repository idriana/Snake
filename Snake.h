#include <vector>
#include <random>
#include "windows.h"

#ifndef CPPPRJ_SNAKE_H
#define CPPPRJ_SNAKE_H

#define Empty_id 0
#define Wall_id 1
#define Snake_id 2
#define Apple_id 3

#define pass (void)0

struct Cell {
    int x;
    int y;

    explicit Cell(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }

    Cell operator+(const Cell &other) const {
        return Cell(x + other.x, y + other.y);
    }

    bool operator==(const Cell &other) const {
        return x == other.x and y == other.y;
    }

    bool operator!=(const Cell &other) const {
        return x != other.x or y != other.y;
    }

    friend std::ostream &operator<<(std::ostream &out, const Cell &cell) {
        out << "cell at x =" << cell.x << " y = " << cell.y << std::endl;
        return out;
    }
};

struct Field {
public:
    int size;
    std::vector<std::vector<int>> body;
    std::default_random_engine engine;

    explicit Field(int size = 10, float scale = 1) {
        this->size = size;
        std::random_device r;
        this->engine = std::default_random_engine(r());
        for (int i = 0; i < size; i++) {
            std::vector<int> obj_column;
            for (int j = 0; j < size; j++) {
                if (i == 0 or j == 0 or i == size - 1 or j == size - 1)
                    obj_column.emplace_back(Wall_id);
                else
                    obj_column.emplace_back(Empty_id);

            }
            body.push_back(obj_column);
            obj_column.clear();
        }
    }

    void create_apple() {
        std::uniform_int_distribution<int> x_distribution(1, size - 2);
        std::uniform_int_distribution<int> y_distribution(1, size - 2);
        int x = x_distribution(engine);
        int y = y_distribution(engine);
        while (body[x][y] != Empty_id) {
            x = x_distribution(engine);
            y = y_distribution(engine);
        }
        body[x][y] = Apple_id;
    }
};

class Snake {
public:
    Cell delta;
    Cell last_delta;
    std::vector<Cell> body;
    Field field;

    explicit Snake(int size) {
        this->field = Field(size, float(10) / float(size));
        field.create_apple();
        this->delta = Cell(0, -1);
        this->last_delta = delta;
        int x = size / 2;
        int y = size / 2;
        this->body.emplace_back(x, y);
        this->body.emplace_back(x, y + 1);
        field.body[x][y] = Snake_id;
        field.body[x][y + 1] = Snake_id;
    }

    bool new_game() {
        for (int i = 1; i < field.size - 1; i ++) {
            for (int j = 1; j < field.size - 1; j++){
                field.body[i][j] = Empty_id;
            }
        }
        this->delta = Cell(0, -1);
        this->last_delta = delta;
        field.create_apple();
        body.clear();
        int x = field.size / 2;
        int y = field.size / 2;
        this->body.emplace_back(x, y);
        this->body.emplace_back(x, y + 1);
        field.body[x][y] = Snake_id;
        field.body[x][y + 1] = Snake_id;
        return true;
    }

    void up() {
        if (last_delta + Cell(0, -1) != Cell(0, 0))
            delta = Cell(0, -1);
    }

    void right() {
        if (last_delta + Cell(1, 0) != Cell(0, 0))
            delta = Cell(1, 0);
    }

    void left() {
        if (last_delta + Cell(-1, 0) != Cell(0, 0))
            delta = Cell(-1, 0);
    }

    void down() {
        if (last_delta + Cell(0, 1) != Cell(0, 0))
            delta = Cell(0, 1);
    }

    void base_move() {
        last_delta = delta;
        Cell temp = body[body.size() - 1];
        if (field.body[temp.x][temp.y] != Apple_id)
            field.body[temp.x][temp.y] = Empty_id;
        for (auto i = body.size() - 1; i > 0; i--) {
            body[i] = body[i - 1];
            field.body[body[i].x][body[i].y] = Snake_id;
        }
        body[0] = body[0] + delta;
        temp = body[0];
        field.body[temp.x][temp.y] = Snake_id;
    }

    bool move() {
        Cell next = body[0] + delta;
        switch (field.body[next.x][next.y]) {
            case Empty_id:
                this->base_move();
                return true;
            case Apple_id:
                body.push_back(body[body.size() - 1]);
                this->base_move();
                if (body.size() < (field.size-2) * (field.size-2)) {
                    field.create_apple();
                    return true;
                } else
                    return false;
            case Wall_id:
                return false;
            case Snake_id:
                if (next == body[body.size() - 1]) {
                    this->base_move();
                    return true;
                }
                return false;
            default:
                break;
        }
    }
};

#endif //CPPPRJ_SNAKE_H
