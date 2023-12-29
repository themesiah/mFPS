# TODO

- Make RenderableObject abstract. Create RenderableModel that extends RenderableObject. Sprite will extend from RenderableObject too.
- Create a MaterialFactory to be used inside MeshFactory (or wherever).
- Create a TextureManager to reuse already loaded textures.
- Create an ActionManager to not depend on raw inputs.
- Integrate ImGUI just for debug builds.
- Do a first take on forward illumination.