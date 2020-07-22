#include "SpaceDeliverersCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interactive.h"
#include "Instrument.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InteractionComponent.h"
#include "Components/InventoryComponent.h"
#include "Utils/TagStrings.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SpaceLevelScript.h"

ASpaceDeliverersCharacter::ASpaceDeliverersCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;	
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	InteractionBox = CreateDefaultSubobject<UBoxComponent >(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ASpaceDeliverersCharacter::OnOverlapBegin);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &ASpaceDeliverersCharacter::OnOverlapEnd);

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	Tags.Add(TagStrings::PlayerTag);
}


void ASpaceDeliverersCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASpaceDeliverersCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASpaceDeliverersCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &ASpaceDeliverersCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASpaceDeliverersCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &ASpaceDeliverersCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASpaceDeliverersCharacter::LookUpAtRate);
	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &ASpaceDeliverersCharacter::OnFire);
	PlayerInputComponent->BindAction("RMB", IE_Pressed, this, &ASpaceDeliverersCharacter::OnRelease);
	PlayerInputComponent->BindAction("Esc", IE_Pressed, this, &ASpaceDeliverersCharacter::OnEscPressed);
}

void ASpaceDeliverersCharacter::BeginPlay()
{
	Super::BeginPlay();
	InteractionComponent->OnInstrumentChanged.AddDynamic(this, &ASpaceDeliverersCharacter::OnInstrumentChanged);

	if (IsNeedCameraAnimation)
	{
		StartCameraAnimation();
	}
}

void ASpaceDeliverersCharacter::OnInstrumentChanged(int typeInt)
{
	InstrumentType type = (InstrumentType)typeInt;
	if (InteractionBoxScaleFactor != 1 && type == InstrumentType::None) {
		ScaleInteractionBox(1);
	}
	else if (InteractionBoxScaleFactor == 1 && type == InstrumentType::Gun) {
		ScaleInteractionBox(6);
	}
}

void ASpaceDeliverersCharacter::Turn(float Value)
{
	if (IsRotationEnabled) {
		AddControllerYawInput(Value);
	}
}

void ASpaceDeliverersCharacter::LookUp(float Value)
{
	if (IsRotationEnabled) {
		AddControllerPitchInput(Value);
	}
}

void ASpaceDeliverersCharacter::TurnAtRate(float Rate)
{
	if (IsRotationEnabled) {
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void ASpaceDeliverersCharacter::LookUpAtRate(float Rate)
{
	if (IsRotationEnabled) {
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void ASpaceDeliverersCharacter::ScaleInteractionBox(const int& coeff)
{
	InteractionBoxScaleFactor = coeff;
	InteractionBox->SetRelativeScale3D(FVector(coeff, 1, 1));
	InteractionBox->SetRelativeLocation(FVector(BoxOffset + (coeff - 1) * 32, 0, -15));
}

void ASpaceDeliverersCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASpaceDeliverersCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ASpaceDeliverersCharacter::OnFire() 
{
	if (InteractionComponent->GetInstrument() != NULL) {
		OnFireBP(InteractionComponent->GetInstrument()->GetType());
	}
	InteractionComponent->OnFire();
}

void ASpaceDeliverersCharacter::OnRelease() 
{
	InteractionComponent->OnRelease();
}

void ASpaceDeliverersCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IInteractive* inter = Cast<IInteractive>(OtherActor);
	if (inter != NULL && inter->IsActiveForInteraction) {
		InteractionComponent->OnSelect(inter);
	}
}

void ASpaceDeliverersCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (InteractionComponent->GetInteractive() != nullptr && OtherActor == InteractionComponent->GetInteractive()->_getUObject()) {
		InteractionComponent->OnDeselect();
	}
}

void ASpaceDeliverersCharacter::StartCameraAnimation()
{
	ASpaceLevelScript* level = Cast<ASpaceLevelScript>(GetWorld()->GetLevelScriptActor());
	const AActor* cameraStartPoint = level->GetPlayerCameraStart();
	FVector startLocation = GetTransform().InverseTransformPosition(GetActorLocation());
	//FRotator startRotation = GetTransform().InverseTransformRotation(GetActorRotation());

	FollowCamera->SetWorldLocation(cameraStartPoint->GetActorLocation());
	FollowCamera->SetWorldRotation(cameraStartPoint->GetActorRotation());

	DisableMovement(CameraAnimationDuration);

	FLatentActionInfo ActionInfo;
	ActionInfo.CallbackTarget = this;
	ActionInfo.Linkage = 0;
	IsRotationEnabled = false;
	ActionInfo.ExecutionFunction = "OnCameraAnimationEnd";
	UKismetSystemLibrary::MoveComponentTo(FollowCamera, startLocation, FRotator::ZeroRotator,
		false, false, CameraAnimationDuration, false,
		EMoveComponentAction::Move, ActionInfo);
}

void ASpaceDeliverersCharacter::OnCameraAnimationEnd()
{
	IsRotationEnabled = true;
}

void ASpaceDeliverersCharacter::OnEscPressed()
{
	FGenericPlatformMisc::RequestExit(false);
}
