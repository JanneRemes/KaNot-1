#include <SpriteBatch.h>	
#include <cassert>
#include <string>

SpriteBatch::SpriteBatch()
{
	defaults();
}
SpriteBatch::~SpriteBatch()
{
	destroy();
}

void SpriteBatch::begin()
{
	assert(!_isActive);

	_isActive = true;
	_spriteCount = 0;

}
void SpriteBatch::end()
{
	assert(_isActive);

	if(_spriteCount > 0)
	{
		prepareSorting();
		prepareRendering();
		render();
	}

	_isActive = false;
}

void SpriteBatch::draw(const Texture* texture, const glm::vec2 position)
{
	assert(_isActive);
	//createSprite(texture, position, kusoRectangle::empty(), glm::vec2());
}

void SpriteBatch::defaults()
{
	//_shader = NULL;
	//_vertexBuffer = NULL;
	//_indexBuffer = NULL;

	//_vertexPositions = NULL;
	//_vertexTextureCoords = NULL;
	//_vertexOffset = 0;

	//_projectionTransform = glm::mat4::_inverse identity();
	
	_sprites = NULL;
	_spriteCount = 0;

	_isActive = false;

}

void SpriteBatch::initialize()
{
	initializeShader();
	initializeBuffers();
	//initializeProjectionTransform();
	initializeSprites();


}
void SpriteBatch::destroy()
{
	delete[] _sprites;

	//delete _indexBuffer;
	//delete _vertexBuffer;
	//delete _shader;

}
void SpriteBatch::prepareRendering()
{

}
void SpriteBatch::render()
{

}
void SpriteBatch::initializeShader()
{

}
void SpriteBatch::initializeBuffers()
{

}
void SpriteBatch::initializeSprites()
{

}
void SpriteBatch::initializeSorting()
{

}
void SpriteBatch::prepareSorting()
{

}
void SpriteBatch::renderBatch(const Texture* texture, const Sprite* sprites, const int spriteCount)
{

}
void SpriteBatch::clearBuffers()
{

}
void SpriteBatch::renderSprite(const Sprite* sprite)
{

}
//glm::mat3 SpriteBatch::createTransform(const Sprite* sprite)
//{
//
//}
void SpriteBatch::createVertexPositions(const Sprite* sprite, const glm::mat3& transform)
{

}
void SpriteBatch::createVertexTextureCoords(const Sprite* sprite)
{

}
void SpriteBatch::createIndices()
{

}

//void SpriteBatch::createSprite(const Texture* texture, const glm::vec2& topLeft, const glm::vec2& bottomRight, const kusoRectangle& source, const glm::vec2& origin, const float rotationAngle = 0.0f)
//{
//
//}
