#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "Snake.h"

TEST_CASE("Direction check") {
    Snake snake(10);
    CHECK (snake.delta == Vector(0, -1));
    snake.left();
    CHECK (snake.delta == Vector(-1, 0));
    snake.right();
    CHECK (snake.delta == Vector(1, 0));
    snake.down();
    CHECK (snake.delta == Vector(1, 0));
    snake.move();
    snake.down();
    CHECK (snake.delta == Vector(0, 1));
}

TEST_CASE("Eating apple check") {
    Snake snake(10);
    Vector next = snake.body[0] + snake.delta;
    Vector tail = snake.body[snake.body.size() - 1];
    snake.field.body[next.x][next.y] = Apple_id;
    int size = snake.body.size();
    snake.move();
    CHECK(snake.body.size() == size + 1);
    CHECK(snake.body[snake.body.size() - 1] + snake.delta == snake.body[snake.body.size() - 2]);
    Vector head = snake.body[0];
    CHECK(snake.field.body[head.x][head.y] == Snake_id);
    CHECK(next == head);
    CHECK(tail == snake.body[snake.body.size() - 1]);
}

TEST_CASE("Wall crush check") {
    Snake snake(6);
    Vector next = snake.body[0] + snake.delta;
    CHECK(snake.move() == true);
    CHECK(snake.body[0] == next);
    next = snake.body[0] + snake.delta;
    CHECK(snake.move() == true);
    CHECK(snake.body[0] == next);
    CHECK(snake.move() == false);
    CHECK(snake.body[0] == next);
}

TEST_CASE("Troubleproof move check") {
    Snake snake(6);
    Vector next = snake.body[0] + snake.delta;
    snake.base_move();
    CHECK(snake.body[0] == next);
    next = snake.body[0] + snake.delta;
    snake.base_move();
    CHECK(snake.body[0] == next);
    next = snake.body[0] + snake.delta;
    CHECK(snake.field.body[next.x][next.y] == Wall_id);
    snake.base_move();
    CHECK(snake.body[0] == next);
}

TEST_CASE("Self crush check") {
    Snake snake(10);
    Vector next = snake.body[0] + snake.delta;
    snake.field.body[next.x][next.y] = Apple_id;
    CHECK(snake.move());
    snake.left();
    next = snake.body[0] + snake.delta;
    snake.field.body[next.x][next.y] = Apple_id;
    CHECK(snake.move());
    snake.down();
    next = snake.body[0] + snake.delta;
    snake.field.body[next.x][next.y] = Apple_id;
    CHECK(snake.move());
    snake.right();
    CHECK(snake.move() == false);
}

TEST_CASE("Win check") {
    Snake snake(6);
    Vector next = snake.body[0] + snake.delta;
    for (int i = 1; i < snake.field.body.size() - 1; i++)
        for (int j = 1; j < snake.field.body[0].size() - 1; j++)
            if (snake.field.body[i][j] != Snake_id and Vector(i, j) != next) {
                snake.field.body[i][j] = Snake_id;
                snake.body.emplace_back(i, j);
            }
    snake.field.body[next.x][next.y] = Apple_id;
    CHECK(snake.body.size() == 15);
    CHECK(not snake.move());
}

TEST_CASE("Apple gen check") {
    Snake snake(6);
    Vector head = snake.body[0];
    Vector tail = snake.body[1];
    for (int i = 0; i < 13; i++) { //одно из яблок генерируется автоматически при создании экземпляра класса Field
        snake.field.create_apple();
    }
    for (int i = 1; i < 5; i++)
        for (int j = 1; j < 5; j++)
            if (Vector(i, j) != head and Vector(i, j) != tail)
                CHECK(snake.field.body[i][j] == Apple_id);
}

TEST_CASE("Restart check") {
    Snake snake(6);
    Vector head = snake.body[0];
    Vector tail = snake.body[1];
    snake.left();
    for (int i = 1; i < snake.field.body.size() - 1; i++)
        for (int j = 1; j < snake.field.body[0].size() - 1; j++)
            if (snake.field.body[i][j] != Snake_id) {
                snake.field.body[i][j] = Snake_id;
                snake.body.emplace_back(i, j);
            }
    CHECK(snake.delta == Vector(-1, 0));
    CHECK(snake.body.size() == 16);
    CHECK(snake.new_game());
    CHECK(snake.delta == Vector(0, -1));
    for (int i = 1; i < 5; i++)
        for (int j = 1; j < 5; j++)
            if (Vector(i, j) != head and Vector(i, j) != tail)
                CHECK(snake.field.body[i][j] != Snake_id);
    CHECK(snake.field.body[head.x][head.y] == Snake_id);
    CHECK(snake.field.body[tail.x][tail.y] == Snake_id);
}
