#include "Texture.h"

#include <vector>

#include <glm/glm.hpp>
#include <glm/ext.hpp>



class SpriteBatch
{
public:

	SpriteBatch();
	~SpriteBatch();

	void begin();
	void end();

	void draw(const Texture* texture, const glm::vec2 position);

private:

	struct Sprite
	{
		glm::vec2 topLeft;
		glm::vec2 bottomRight;
		glm::vec2 origin;
		const Texture* texture;
		float rotationAngle;
	};

	static const unsigned int MAX_VERTEX_COUNT = 2048;
	static const unsigned int VERTICES_PER_SPRITE = 4;

	Sprite* _sprites;
	std::vector<Sprite*> _sortedSprites;
	unsigned int _spriteCount;

	bool _isActive;

	SpriteBatch(const SpriteBatch& spriteBatch);

	void defaults();

	void initialize();
	void destroy();
	void prepareRendering();
	void render();

	void createSprite(const Texture* texture, const glm::vec2& topLeft, const glm::vec2& bottomRight, const devmath::Rectangle& source, const glm::vec2& origin, const float rotationAngle = 0.0f);

};