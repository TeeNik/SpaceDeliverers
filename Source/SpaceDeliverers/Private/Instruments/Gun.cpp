#include "Gun.h"

AGun::AGun() {

}

void AGun::BeginPlay()
{
}

InstrumentType AGun::GetType() const
{
	return InstrumentType::Gun;
}

void AGun::Shoot(AActor * target)
{

}
