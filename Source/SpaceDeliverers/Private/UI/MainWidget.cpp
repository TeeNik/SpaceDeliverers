#include "MainWidget.h"
#include "ProgressBar.h"

void UMainWidget::Init(float value)
{
	ShieldBar->SetPercent(value);
}

void UMainWidget::UpdateShield(float value)
{
	ShieldBar->SetPercent(value);

	//TargetPercent = value;
}

void UMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	UUserWidget::NativeTick(MyGeometry, InDeltaTime);
	
	//float percent = ShieldBar->Percent;
	//if (percent != TargetPercent) {
	//	percent = FMath::Lerp(percent, TargetPercent, .01f);
	//	ShieldBar->SetPercent(percent);
	//}
}
