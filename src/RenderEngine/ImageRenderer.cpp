#include "ImageRenderer.h"

ImageRenderer::ImageRenderer() : mSignalSource(nullptr) {}
ImageRenderer::~ImageRenderer() { stopRendering(); }
void ImageRenderer::renderImage(const std::string &imagePath) {
  // Implementació de la renderització d'imatges
  // Aquí es pot afegir el codi per renderitzar imatges
  // Utilitzant OpenCV o qualsevol altra biblioteca d'imatge
}
void ImageRenderer::stopRendering() {
  // Implementació per aturar la renderització d'imatges
  // Aquí es pot afegir el codi per aturar la renderització
}
