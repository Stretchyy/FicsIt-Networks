#pragma once

#include "CoreMinimal.h"
#include "Json.h"

#include <string>

#include "ProcessorStateStorage.h"

namespace FicsItKernel {
	enum ProcessorArchitecture {
		LUA
	};

	class KernelSystem;

	/**
	 * A Processor handles the whole execution of a program and also makes sure that resource overusage causes a crash.
	 */
	class Processor {
	protected:
		KernelSystem* kernel;

	public:
		virtual ~Processor() {}

		/**
		* Sets the kernel this processor uses.
		*
		* @param[in]	kernel	the new kernel the processor will use
		*/
		void setKernel(KernelSystem* kernel);

		/**
		* Allows to access the connected kernel
		*
		* @return	returns the connected kernel
		*/
		KernelSystem* getKernel();

		/**
		* Does one processor cycle.
		* Processor needs to execute its speed accordingly.
		*
		* Basically redirects the factory tick
		*
		* @param[in]	delta	the delta seconds since last tick
		*/
		virtual void tick(float delta) = 0;

		/**
		* recalculates the processor memory usage
		*
		* @param[in]	recalc	set this to true if you want to force the processor to recalculate its memory usage
		*/
		virtual int64 getMemoryUsage(bool recalc = false) = 0;

		/**
		* Resets the execution state of the processor.
		* f.e. resets the code counter
		*/
		virtual void reset() = 0;

		/**
		 * Serializes the processor state and stores it in the given storage object
		 *
		 * @param[in]	Storage		the serialization storage object which will hold the serialized data
		 */
		virtual void Serialize(UProcessorStateStorage* Storage) = 0;

		/**
		 * Deserializes a storage object to a processor state and loads it
		 *
		 * @param[in]	Storage 	the storage object which holds the serialized data
		 */
		virtual void Deserialize(UProcessorStateStorage* Storage) = 0;

		/**
		 * Creates the storage object used to store serialization data
		 *
		 * @return	The created storage object
		 */
		virtual UProcessorStateStorage* CreateSerializationStorage() = 0;
	};
}
