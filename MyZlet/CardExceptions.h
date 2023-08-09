#pragma once
#include <exception>
#include <string>

namespace crd {

	enum message_type { key, arguments, command };

	class CardException : public std::exception {
	public:
		CardException(const std::string& message, const message_type _type) : error_message(message), type(_type) {}
		const char* what() const noexcept override {
			switch (type){
				case key: 
					this->note = error_message + " Valieble keys: -n, -nh, -g, -gh.";
					break;
				case arguments:
					this->note = "WRONG ARGUMENTS. " + error_message;
					break;
				case command:
					this->note = "WORNG COMMAND. " + error_message;
			}
			return note.c_str();
		}
	private:
		std::string error_message;
		message_type type;
		mutable std::string note;
	};

}