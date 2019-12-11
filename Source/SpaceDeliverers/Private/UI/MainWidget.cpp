#include "MainWidget.h"
#include "ProgressBar.h"

void UMainWidget::UpdateShield(const float& value) 
{
	UE_LOG(LogTemp, Log, TEXT("UpdateShield: %g"), value);
	ShieldBar->SetPercent(value);
}