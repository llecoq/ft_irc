#include "Channel.hpp"

Channel::Channel()
		: _name(), _topic(), _operator_client(), _members() {}

Channel::~Channel() {}

void Channel::broadcast() {(void)_operator_client;}