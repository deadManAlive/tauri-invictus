#pragma once

#include <JuceHeader.h>

namespace taurus {
    template <typename T, int SIZE>
    class LockFreeBufferFixed {
    public:
        LockFreeBufferFixed() noexcept
            : abstractFifo(SIZE) {
            juce::zeromem(myBuffer, SIZE);
        }

        void addToFifo (const T* someData, int numItems) {
            const auto scope = abstractFifo.write (numItems);

            if (scope.blockSize1 > 0) {
                std::copy_n(someData, scope.blockSize1, myBuffer + scope.startIndex1);
            }
            if (scope.blockSize2 > 0) {
                std::copy_n(someData + scope.blockSize1, scope.blockSize2, myBuffer + scope.startIndex2);
            }
        }
 
        void readFromFifo (T* someData, int numItems) {
            const auto scope = abstractFifo.read (numItems);
    
            if (scope.blockSize1 > 0) {
                std::copy_n(myBuffer + scope.startIndex1, scope.blockSize1, someData);
            }
    
            if (scope.blockSize2 > 0) {
                std::copy_n(myBuffer + scope.startIndex2, scope.blockSize2, someData+scope.blockSize1);
            }
        }

        int getFreeSpace() const {
            return abstractFifo.getFreeSpace();
        }

        void clear() {
            abstractFifo.reset();
        }
    private:
        juce::AbstractFifo abstractFifo;
        T myBuffer[SIZE];
    
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LockFreeBufferFixed)
    };
}