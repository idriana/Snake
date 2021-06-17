#ifndef CPPPRJ_SNAKE_H
#define CPPPRJ_SNAKE_H

#include <vector>
#include <random>
#include "windows.h"


///id of empty place
constexpr int Empty_id = 0;
///id of wall
constexpr int Wall_id = 1;
///id of snake part
constexpr int Snake_id = 2;
///id of apple
constexpr int Apple_id = 3;

/** \brief The structure of the radius vector to the cell on the field.
 *
 * The coordinate axes are directed from left to right and from top to bottom.
*/

struct Vector {
    ///vector's x coordinate
    int x;
    ///vector's y coordinate
    int y;

    /** \brief set vector's x and y
     *
     * @param x - int coordinate for the radius vector
     * @param y - int coordinate for the radius vector
     */
    explicit Vector(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }

    /** \brief sum of two vectors
     *
     * @param other - cell vector object
     * @return resulting vector
     */
    Vector operator+(const Vector &other) const {
        return Vector(x + other.x, y + other.y);
    }

    /** \brief equality of two vectors
     *
     * Compares separate x and y coordinates of two vectors
     *
     * @param other - cell vector object
     * @return equality of two vectors
     */
    bool operator==(const Vector &other) const {
        return x == other.x and y == other.y;
    }

    /** \brief inequality of two vectors
     *
     * @param other - cell vector object
     * @return inequality of two vectors
     */
    bool operator!=(const Vector &other) const {
        return x != other.x or y != other.y;
    }

    /** \brief smart stream output called with <<
     *
     * outputs to stream object string with format:
     * (cell at x = {x} y = {y})
     *
     * @param out - stream object
     * @param cell - onject for output
     * @return out stream object with cell object outputed
     */
    friend std::ostream &operator<<(std::ostream &out, const Vector &cell) {
        out << "cell at x =" << cell.x << " y = " << cell.y << std::endl;
        return out;
    }
};

/** \brief field object for the game
 *
 * square field object filled with cell states:
 * 0:Empty_id - if cell is empty.
 * 1:Wall_id - if there is a wall in cell.
 * 2:Snake_id - if there is a snake part in cell.
 * 3:Apple_id - if there is an apple in cell.
 * All ids are #defined at the start of file.
 */
struct Field {
public:
    ///Size of the field.
    int size;
    ///[size * size] matrix of cell states
    std::vector<std::vector<int>> body;
    ///random engine for generating apples
    std::default_random_engine engine;

    /**\brief generates field size*size.
     *
     * Also initialize random engine, filles field with walls
     *
     * @param size - size of the field.
     */
    explicit Field(int size = 10) {
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

    /** \brief creates apple at field
     *
     * uses random engine and linear distribution
     */
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

/** \brief Player snake object that contains field
 *
 */
class Snake {
public:
    ///Vector object that show snake head displacement after one move.
    Vector delta;
    ///Vector object that saves delta after move.
    Vector last_delta;
    ///array of vectors that points out snake's parts.
    std::vector<Vector> body;
    ///field object.
    Field field;

    /** \brief create Snake object
     *
     * Also generate field, apple and base snake body.
     *
     * @param size - size of the field
     */
    explicit Snake(int size) {
        this->field = Field(size);
        field.create_apple();
        this->delta = Vector(0, -1);
        this->last_delta = delta;
        int x = size / 2;
        int y = size / 2;
        this->body.emplace_back(x, y);
        this->body.emplace_back(x, y + 1);
        field.body[x][y] = Snake_id;
        field.body[x][y + 1] = Snake_id;
    }

    /** \brief restart game
     *
     * @return true if game is restarted successfully
     */
    bool new_game() {
        for (int i = 1; i < field.size - 1; i++) {
            for (int j = 1; j < field.size - 1; j++) {
                field.body[i][j] = Empty_id;
            }
        }
        this->delta = Vector(0, -1);
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

    /** \brief change direction to up if it wasn't down
     */
    void up() {
        if (last_delta + Vector(0, -1) != Vector(0, 0))
            delta = Vector(0, -1);
    }

    /** \brief change direction to right if it wasn't left
     */
    void right() {
        if (last_delta + Vector(1, 0) != Vector(0, 0))
            delta = Vector(1, 0);
    }

    /** \brief change direction to left if it wasn't right
     */
    void left() {
        if (last_delta + Vector(-1, 0) != Vector(0, 0))
            delta = Vector(-1, 0);
    }

    /** \brief change direction to down if it wasn't up
     */
    void down() {
        if (last_delta + Vector(0, 1) != Vector(0, 0))
            delta = Vector(0, 1);
    }

    /** \brief move function that ignores obstacles.
     *
     * Changes state of the field and snake's body.
     */
    void base_move() {
        last_delta = delta;
        Vector temp = body[body.size() - 1];
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

    /** \brief default movement function.
     *
     * Check if there is an object on the way, react and move.
     * Can manipulate field state and body length.
     *
     * @return true if there wasn't obstacle, false otherwise
     */
    bool move() {
        Vector next = body[0] + delta;
        switch (field.body[next.x][next.y]) {
            case Empty_id:
                this->base_move();
                return true;
            case Apple_id:
                body.push_back(body[body.size() - 1]);
                this->base_move();
                if (body.size() < (field.size - 2) * (field.size - 2)) {
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
                std::terminate();
        }
    }
};

#endif //CPPPRJ_SNAKE_H
