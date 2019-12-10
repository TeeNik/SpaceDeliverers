#include "MainWidget.h"
#include "ProgressBar.h"

void UMainWidget::UpdateShield(const float& value) 
{
	ShieldBar->SetPercent(value);
}