#include "Renderer.h"
#include "Walnut/Random.h"

void Renderer::Render()
{
	// render every pixel
	for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
	{
		for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++)
		{
			// Get x and y coords in a vec2
			glm::vec2 coord = { (float)x / (float)m_FinalImage->GetWidth(), (float)y / (float)m_FinalImage->GetHeight() };
			// Convert coord to -1 -> 1 range (previously 0 -> 1)
			coord = coord * 2.0f - 1.0f;
			m_FinalImageData[x + y * m_FinalImage->GetWidth()] = PerPixel(coord);
		}
	}

	m_FinalImage->SetData(m_FinalImageData);
}

void Renderer::OnResize(uint32_t width, uint32_t height)
{
	if (m_FinalImage)
	{
		if (m_FinalImage->GetHeight() == height && m_FinalImage->GetWidth() == width)
			return;

		m_FinalImage->Resize(width, height);
	}
	else
	{
		m_FinalImage = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
	}

	delete[] m_FinalImageData;
	m_FinalImageData = new uint32_t[width * height];

}

uint32_t Renderer::PerPixel(glm::vec2 coord)
{

	glm::vec3 rayDir(coord.x, coord.y, -1.0f);
	glm::vec3 rayOrigin(0.0f, 0.0f, 2.0f);
	rayDir = glm::normalize(rayDir);
	
	float radius = 0.5f;

	float a = glm::dot(rayDir, rayDir);
	float b = 2.0f * glm::dot(rayOrigin, rayDir);
	float c = glm::dot(rayOrigin, rayOrigin) - radius * radius;

	float discriminant = b * b - 4.0f * a * c;

	if (discriminant >= 0.0f)
		return 0xffff00ff;
	
	return 0xff000000;
}


