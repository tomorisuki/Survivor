#include "TextRender.h"

#include "GameObject.h"

void TextRender::Start()
{
}

void TextRender::Update(float deltaTime)
{
}

void TextRender::Render()
{
	if (!enable || text.empty() || !font) return;

	if (isDirty) {
		SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(),0,color);
		if (surface) {
			if (texture) SDL_DestroyTexture(texture);
			texture = SDL_CreateTextureFromSurface(engine->GetRenderSystem()->GetSdlRenderer(), surface);
			SDL_DestroySurface(surface);
			isDirty = false;
		}
	}
	Transform transform = owner->transform;
	transform.position += offset;

	engine->GetRenderSystem()->RenderUIText(texture, transform);
}

void TextRender::SetText(const std::string& text)
{
	if (this->text != text) {
		isDirty = true;
	}
	this->text = text;
}

void TextRender::SetFont(TTF_Font* font)
{
	this->font = font;
}

void TextRender::SetColor(const SDL_Color& color)
{
	if (!(this->color.a == color.a && this->color.b == color.b && this->color.g == color.g
		&& this->color.r == color.r))
		isDirty = true;
	this->color = color;
}

void TextRender::SetEnable(bool enable)
{
	this->enable = enable;
}

void TextRender::SetOffset(const Vector2D& offset)
{
	this->offset = offset;
}
