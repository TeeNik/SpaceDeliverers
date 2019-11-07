#include "Wrench.h"

void AWrench::Use() {

	GLog->Log("Use Wrench");

}

InstrumentType AWrench::GetType() const
{
	return InstrumentType::Wrench;
}
