#include "AssetManager.h"

namespace SDLFramework {
	AssetManager* AssetManager::sInstance = nullptr;

	AssetManager* AssetManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new AssetManager();
		}

		return sInstance;
	}

	void AssetManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}



	SDL_Texture* AssetManager::getTexture(std::string filename, bool managed) {
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("Assets/" + filename);

		if (mTextures[fullPath] == nullptr) {
			mTextures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);
		}

		if (mTextures[fullPath] != nullptr && managed) {
			mTextureRefCount[mTextures[fullPath]] += 1;
		}

		return mTextures[fullPath];
	}

	SDL_Texture* AssetManager::getText(std::string text, std::string filename, int size, SDL_Color color, bool managed) {
		std::stringstream ss;

		ss << size << (int)color.r << (int)color.g << (int)color.b;
		std::string key = text + filename + ss.str();

		if (mTextures[key] == nullptr) {
			TTF_Font* font = getFont(filename, size);
			mTextures[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
		}

		if (mTextures[key] != nullptr && managed) {
			mTextureRefCount[mTextures[key]] += 1;
		}

		return mTextures[key];

	}

	TTF_Font* AssetManager::getFont(std::string filename, int size) {
		std::string fullpath = SDL_GetBasePath();
		fullpath.append("Assets/" + filename);

		std::stringstream ss;
		ss << size;
		std::string key = fullpath + ss.str();

		if (mFonts[key] == nullptr) {
			mFonts[key] = TTF_OpenFont(fullpath.c_str(), size);

			if (mFonts[key] == nullptr) {
				std::cerr << "Unable to load Font: " << filename << "! TTF Error: " << TTF_GetError() << "\n";
			}
		}

		return mFonts[key];
	}

	void AssetManager::DestroyTexture(SDL_Texture* texture) {
		std::map<SDL_Texture*, unsigned>::iterator it = mTextureRefCount.find(texture);

		if (it != mTextureRefCount.end()) {
			it->second -= 1;
			if (it->second == 0) {
				//this means no more instances of the texture are being used
				UnloadTexture(it->first);
				mTextureRefCount.erase(it->first);
			}

		}
		else {
			//otherwise, something is still making a reference to this texture.
			UnloadTexture(texture);
		}
	}

	AssetManager::AssetManager() {

	}

	AssetManager::~AssetManager() {
		for (auto tex : mTextures) {
			if (tex.second != nullptr) {
				SDL_DestroyTexture(tex.second);
			}

		}
		mTextures.clear();
	}

	void AssetManager::UnloadTexture(SDL_Texture* texture) {
		bool found = false;
		std::string key;
		std::map<std::string, SDL_Texture*>::iterator it;

		for (it = mTextures.begin(); it != mTextures.end() && !found; it++) {
			if ((found = it->second == texture)) {
				SDL_DestroyTexture(it->second);
				key = it->first;
			}
		}

		if (found) {
			mTextures.erase(key);
		}
	}
}