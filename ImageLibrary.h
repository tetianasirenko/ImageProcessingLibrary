#pragma once
#include <string>
#include <vector>

#include "ImageProcessingLibrary.h"
#include "ImageProcessingLibraryImpl.h"

template <typename Image>
struct Result
{
	bool finishProcessing = false;
	Image processedImage = nullptr;
};


class ImageLibrary
{
private:
	static ImageLibrary* mLibrary;
	ImageProcessingLibrary mImageProcessing;

	ImageLibrary(ImageProcessingLibrary imageProcessing)
		:mImageProcessing(imageProcessing)
	{}


public:
	/**
	* Get ImageProcessing library instance. Should always be used before calling another library method.
	* Use like ImageLibrary::Get()->getSupportedOperationsList()
	* @return library instance.
	*/
	static ImageLibrary*  Get()
	{
		if (mLibrary == nullptr)
		{
			mLibrary = new ImageLibrary(ImageProcessingLibraryImpl());
		}

		return mLibrary;
	}

	/**
	* Return all supported in library operations.
	* @return list of supported operations.
	*/
	std::vector<std::string> getSupportedOperationsList();

	/**
	* Start image processing for selected operation.
	* @param operationName name of operation.
	* @param Image input image.
	* @param Args list of parameters for selected operation. Can be different number for different operation.
	* @return -1 in case if operation not supported. If operation supported - id of current processing operation. This id should be used for getting processing result.
	*/
	template<typename Image, typename... Args>
	int runOperation(std::string operationName, Image, Args...);

	/**
	* Return is of all processing image operations.
	* @return list of processing images ids.
	*/
	std::vector<int> getCurrentOperations();

	/**
	* Cancel selected image processing operation.
	* @param id image processing operation id
	*/
	void cancelOperation(const int id);

	/**
	* Cancel all images processing operation.
	*/
	void cancelAllOperations();

	/**
	* Cancel all images processing operation.
	* @param id image processing operation id.
	* @return processing result as structure Result that contain 2 field - finishProcessing and processedImage.
	* If Result.finishProcessing is true - processing for image finished. Result image is in Result.processedImage field.
	* If Result.finishProcessing is false - processing not finished.  Result.processedImage is null.
	*/
	template<typename Image>
	Result<Image> getOperationResult(const int id);
};

