#pragma once
#include "Graphics.h"
#include <map>
#include <sstream>

namespace SDLFramework {
	class AssetManager {
	public:
		static AssetManager* Instance();
		static void Release();

		SDL_Texture* getTexture(std::string filename, bool managed = false);
		SDL_Texture* getText(std::string text, std::string filename, int size, SDL_Color color, bool managed = false);

		void DestroyTexture(SDL_Texture* texture);


	private:
		AssetManager();
		~AssetManager();

		void UnloadTexture(SDL_Texture* texture);
		TTF_Font* getFont(std::string filename, int size);

		static AssetManager* sInstance;
				
				//Key			Value
		std::map<std::string, SDL_Texture*> mTextures;
		std::map<std::string, TTF_Font*> mFonts;
		std::map<SDL_Texture*, unsigned> mTextureRefCount;
	};








}
