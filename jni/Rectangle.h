#pragma once
#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class kusoRectangle
{
public:

        int x;
        int y;
        int width;
        int height;

        kusoRectangle();
        kusoRectangle(const int x, const int y, const int width, const int height);
        kusoRectangle(const glm::vec2& position, const glm::vec2& dimensions);
        kusoRectangle(const kusoRectangle& rectangle);

        ~kusoRectangle();

        int left() const;
        int right() const;
        int top() const;
        int bottom() const;
        glm::vec2 topLeft() const;
        glm::vec2 bottomRight() const;
        bool isEmpty() const;

        kusoRectangle combine(const kusoRectangle& rectangle) const;

        bool contains(const int x, const int y) const;

        bool contains(const glm::vec2& point) const;

        void inflate(const int amountX, const int amountY);

        void inflate(const glm::vec2& amount);

        bool intersects(const kusoRectangle& rectangle) const;

        void offset(const int amountX, const int amountY);

        void offset(const glm::vec2& amount);

        static kusoRectangle empty();

        kusoRectangle& operator =(const kusoRectangle& rectangle);

        bool operator ==(const kusoRectangle& rectangle) const;

        bool operator !=(const kusoRectangle& rectangle) const;

        friend std::ostream& operator <<(std::ostream& output, const kusoRectangle& rectangle);
};