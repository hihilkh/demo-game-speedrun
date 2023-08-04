#include "GE/GEHeader.h"
#include "PlayerStateMachine.h"
#include "GE/Utils/EnumUtils.h"
#include "Character/Player/PlayerModel.h"
#include "PlayerStateRequest.h"

#include "Handler/PlayerWalkStateHandler.h"
#include "Handler/PlayerPrepareToRunStateHandler.h"
#include "Handler/PlayerRunStateHandler.h"
#include "Handler/PlayerStopRunningStateHandler.h"
#include "Handler/PlayerFallbackStateHandler.h"

namespace Player
{
	PlayerStateMachine::PlayerStateMachine(PlayerModel& model) :
		model(model),
		stateHandler(nullptr)
	{
		ChangeState(PlayerState::Walk);
	}

	PlayerStateMachine::~PlayerStateMachine() = default;

	PlayerState PlayerStateMachine::GetState() const
	{
		return stateHandler->GetState();
	}

	void PlayerStateMachine::AddStateRequest(PlayerStateRequest request)
	{
		stateRequests.push_back(request);
	}

	void PlayerStateMachine::Update()
	{
		DetermineState();
		stateHandler->OnUpdate();
	}

#pragma region UpdateState

	void PlayerStateMachine::DetermineState()
	{
		PlayerState currentState = GetState();
		switch (currentState) {
			case PlayerState::Walk:
				DetermineState_Walk();
				break;
			case PlayerState::PrepareToRun:
			case PlayerState::Run:
			case PlayerState::StopRunning:
				DetermineState_Run();
				break;
			case PlayerState::Fallback:
				DetermineState_Fallback();
				break;
			default:
				DEBUG_LOG_WARNING("DetermineState : PlayerState::" << GE::Enum::ToString(currentState) << "についてはまだ実装していない。");
				break;
		}

		stateRequests.clear();
	}

	void PlayerStateMachine::DetermineState_Walk()
	{
		for (auto request : stateRequests) {
			switch (request) {
				case PlayerStateRequest::StartRunning:
					ChangeState(PlayerState::PrepareToRun);
					return;
			}
		}
	}

	void PlayerStateMachine::DetermineState_Run()
	{
		PlayerState currentState = GetState();
		PlayerState nextState = currentState;
		for (auto& request : stateRequests) {
			switch (request) {
				case PlayerStateRequest::StopRunning:
					nextState = currentState == PlayerState::Run ? PlayerState::StopRunning : PlayerState::Walk;
					break;
				case PlayerStateRequest::CrashWithWall:
					ChangeState(PlayerState::Fallback);
					return;
				case PlayerStateRequest::HitWall:
					if (currentState == PlayerState::StopRunning) {
						ChangeState(PlayerState::Walk);
						return;
					}
					break;
			}
		}

		if (nextState != currentState) {
			ChangeState(nextState);
			return;
		}

		switch (currentState) {
			case PlayerState::PrepareToRun:
				if (stateHandler->CheckHasDoneState()) {
					ChangeState(PlayerState::Run);
				}
				break;
			case PlayerState::StopRunning:
				if (stateHandler->CheckHasDoneState()) {
					ChangeState(PlayerState::Walk);
				}
				break;
		}
	}

	void PlayerStateMachine::DetermineState_Fallback()
	{
		if (stateHandler->CheckHasDoneState()) {
			ChangeState(PlayerState::Walk);
		}
	}

#pragma endregion

	void PlayerStateMachine::ChangeState(PlayerState state)
	{
		if (stateHandler) {
			if (GetState() == state) {
				DEBUG_LOG("PlayerはすでにPlayerState::" << GE::Enum::ToString(state) << "になった。ChangeStateの必要がない。");
				return;
			}
			stateHandler->OnExit();
		}

		stateHandler = CreateStateHandler(state);
		stateHandler->OnEnter();
	}

	std::unique_ptr<PlayerStateHandler> PlayerStateMachine::CreateStateHandler(PlayerState state) const
	{
		switch (state) {
			case PlayerState::Walk:
				return std::make_unique<PlayerWalkStateHandler>(model);
			case PlayerState::PrepareToRun:
				return std::make_unique<PlayerPrepareToRunStateHandler>(model);
			case PlayerState::Run:
				return std::make_unique<PlayerRunStateHandler>(model);
			case PlayerState::StopRunning:
				return std::make_unique<PlayerStopRunningStateHandler>(model);
			case PlayerState::Fallback:
				return std::make_unique<PlayerFallbackStateHandler>(model);
		}

		DEBUG_LOG_WARNING("CreateStateHandler : PlayerState::" << GE::Enum::ToString(state) << "についてはまだ実装していない。PlayerWalkStateHandlerを使う。");
		return std::make_unique<PlayerWalkStateHandler>(model);
	}
}