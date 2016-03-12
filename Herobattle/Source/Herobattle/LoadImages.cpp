// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "LoadImages.h"
#include "../ImageWrapper/Public/Interfaces/IImageWrapperModule.h"




UTexture2D* ULoadImages::LoadSkillImage(FString name)
{
	UTexture2D* Texture = nullptr;

	FString projectDir = FPaths::GameDir();
	FString FileName = name.Replace(TEXT(" "), TEXT("_")) + TEXT(".jpg");
	FString TexturePath = projectDir + TEXT("/Content/SkillImages/") + FileName;

	// Represents the entire file in memory.
	TArray<uint8> RawFileData;

	if (FFileHelper::LoadFileToArray(RawFileData, *TexturePath))
	{
		IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
		IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);

		if (FFileHelper::LoadFileToArray(RawFileData, *TexturePath))
		{
			if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
			{
				const TArray<uint8>* UncompressedBGRA = nullptr;
				if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
				{
					Texture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

					// Fill in the source data from the file
					void* TextureData = Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
					FMemory::Memcpy(TextureData, UncompressedBGRA->GetData(), UncompressedBGRA->Num());
					Texture->PlatformData->Mips[0].BulkData.Unlock();
					Texture->UpdateResource();
				}
			}
		}
	}

	return Texture;
}