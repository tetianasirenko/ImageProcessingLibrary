## ImageLibrary

Class __ImageLibrary__ contains methods for images processing.
__ImageLibrary__ use singleton pattern. 

Class __ImageLibrary__ use __ImageProcessingLibrary__ interface which contains all image processing logic. __ImageProcessingLibrary__ interface implementation is in __ImageProcessingLibraryImpl__ class. Concrete implementation are injected in __ImageLibrary__ at constructor. (Also can be done using factory in future). 

Class __ImageProcessingLibraryImpl__ contains additional private fields for storing supported operations list, operation results and etc. 
For each image operation creates task. All these tasks are process at __TaskProcessing__ interface instance. __TaskProcessing__ purpose is to manage task execution including resource control, resource optimization and etc. Image processing result are returned using callback function. 

Class __ImageProcessingLibraryImpl__ use __TaskProcessingImpl__ as concrete implementation of __TaskProcessing__ interface. This implementation should be invoked at __ImageProcessingLibraryImpl__ constructor. This approach allows to create mocks for testing and change task managing (if its will be need in future). 

All concrete image processing are implemented at different classes (one for each operation) - __BlurOperation__, __WaterColorOperation__... All these classes implement __ImageOperation__ interface. Concrete implementation should be choosen when creating processing task. It can be Strategy pattern. 
