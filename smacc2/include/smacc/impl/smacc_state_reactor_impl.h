/*****************************************************************************************************************
 * ReelRobotix Inc. - Software License Agreement      Copyright (c) 2018
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/

#pragma once
#include <smacc/smacc_state_reactor.h>
#include <smacc/introspection/introspection.h>

namespace smacc
{

template <typename EventType>
void StateReactor::postEvent(const EventType &ev)
{
    ownerState->postEvent(ev);
}

template <typename EventType>
void StateReactor::postEvent()
{
    ownerState->postEvent<EventType>();
}

template <typename TEv>
void StateReactor::setOutputEvent()
{
    this->postEventFn = [this]() {
        RCLCPP_INFO_STREAM(this->getNode()->get_logger(),"[State Reactor Base] postingfn posting event: " << demangleSymbol<TEv>());
        auto *ev = new TEv();
        this->ownerState->getStateMachine().postEvent(ev);
    };
}

template <typename TEv>
void StateReactor::addInputEvent()
{
    this->eventTypes.push_back(&typeid(TEv));
}

template <typename T, typename TClass>
void StateReactor::createEventCallback(void (TClass::*callback)(T *), TClass *object)
{
    const auto *eventtype = &typeid(T);
    this->eventCallbacks_[eventtype] = [=](void *msg) {
        T *evptr = (T *)msg;
        (object->*callback)(evptr);
    };
}

template <typename T>
void StateReactor::createEventCallback(std::function<void(T *)> callback)
{
    const auto *eventtype = &typeid(T);
    this->eventCallbacks_[eventtype] = [=](void *msg) {
        T *evptr = (T *)msg;
        callback(evptr);
    };
}

namespace introspection
{

template <typename TEv>
void StateReactorHandler::addInputEvent()
{
    StateReactorCallbackFunctor functor;
    functor.fn = [=](std::shared_ptr<smacc::StateReactor> sr) {
        RCLCPP_INFO(nh_->get_logger(),"[%s] State Reactor adding input event: %s", demangleType(srInfo_->stateReactorType).c_str(), demangledTypeName<TEv>().c_str());
        sr->addInputEvent<TEv>();
    };

    this->callbacks_.push_back(functor);

    auto evtype = TypeInfo::getFromStdTypeInfo(typeid(TEv));
    auto evinfo = std::make_shared<SmaccEventInfo>(evtype);
    EventLabel<TEv>(evinfo->label);

    srInfo_->sourceEventTypes.push_back(evinfo);
}

template <typename TEv>
void StateReactorHandler::setOutputEvent()
{
    StateReactorCallbackFunctor functor;
    functor.fn = [=](std::shared_ptr<smacc::StateReactor> sr) {
        RCLCPP_INFO(nh_->get_logger(),"[%s] State Reactor setting output event: %s", demangleType(srInfo_->stateReactorType).c_str(), demangledTypeName<TEv>().c_str());
        sr->setOutputEvent<TEv>();
    };

    this->callbacks_.push_back(functor);
}
} // namespace introspection

} // namespace smacc