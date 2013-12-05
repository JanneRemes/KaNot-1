#include <Rectangle.h>

kusoRectangle::kusoRectangle() { }

kusoRectangle::kusoRectangle(const int x, const int y, const int width, const int height)
        : x(x),
          y(y),
          width(width),
          height(height) { }

kusoRectangle::kusoRectangle(const glm::vec2& position, const glm::vec2& dimensions)
        : x(position.x),
          y(position.y),
          width(dimensions.x),
          height(dimensions.y) { }

kusoRectangle::kusoRectangle(const kusoRectangle& rectangle)
        : x(rectangle.x),
          y(rectangle.y),
          width(rectangle.width),
          height(rectangle.height) { }

kusoRectangle::~kusoRectangle() { }


// Public

int kusoRectangle::left() const
{
        return x;
}

int kusoRectangle::right() const
{
        return x + width;
}

int kusoRectangle::top() const
{
        return y;
}

int kusoRectangle::bottom() const
{
        return y + height;
}

glm::vec2 kusoRectangle::topLeft() const
{
        return glm::vec2(left(), top());
}

glm::vec2 kusoRectangle::bottomRight() const
{
        return glm::vec2(right(), bottom());
}

bool kusoRectangle::isEmpty() const
{
        return *this == empty();
}

//Rectangle Rectangle::combine(const Rectangle& rectangle) const
//{
//        const glm::vec2 position = topLeft().minimum(rectangle.topLeft());
//        const glm::vec2 rightBottom = bottomRight().maximum(rectangle.bottomRight());
//
//        const int _width = rightBottom.x - position.x;
//        const int _height = rightBottom.y - position.y;
//
//        return Rectangle(position.x, position.y, _width, _height);
//}

bool kusoRectangle::contains(const int x, const int y) const
{
        return x >= left() && x <= right() && y >= top() && y <= bottom();
}

bool kusoRectangle::contains(const glm::vec2& point) const
{
        return contains(point.x, point.y);
}

void kusoRectangle::inflate(const int amountX, const int amountY)
{
        width += amountX;
        height += amountY;
}

void kusoRectangle::inflate(const glm::vec2& amount)
{
        return inflate(amount.x, amount.y);
}

bool kusoRectangle::intersects(const kusoRectangle& rectangle) const
{
        return !(left() > rectangle.right() || right() < rectangle.left() ||
                top() > rectangle.bottom() || bottom() < rectangle.top());
}

void kusoRectangle::offset(const int amountX, const int amountY)
{
        x += amountX;
        y += amountY;
}

void kusoRectangle::offset(const glm::vec2& amount)
{
        return offset(amount.x, amount.y);
}

// Static

kusoRectangle kusoRectangle::empty()
{
        return kusoRectangle(0, 0, 0, 0);
}

// Operators

kusoRectangle& kusoRectangle::operator =(const kusoRectangle& rectangle)
{
        if(this != &rectangle)
        {
                x = rectangle.x;
                y = rectangle.y;
                width = rectangle.width;
                height = rectangle.height;
        }

        return *this;
}

bool kusoRectangle::operator ==(const kusoRectangle& rectangle) const
{
        return x == rectangle.x && y == rectangle.y && width == rectangle.width && height == rectangle.height;
}

bool kusoRectangle::operator !=(const kusoRectangle& rectangle) const
{
        return !(*this == rectangle);
}