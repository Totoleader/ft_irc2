#ifndef __Mode_Command_H__
#define __Mode_Command_H__

#include "Libs.hpp"

class Mode_Command : public ACommand
{
private:
	typedef enum e_operation {
		OP_ADD,
		OP_REMOVE
	}	t_operation;

	typedef struct s_mode {
		char			mode;
		t_operation		operation;
	}	t_mode;

	typedef enum e_action {
		NONE,
		SHOW,
		CHANGE
	}	t_action;

	t_action		_action;
	string			_availableModes;
	Channel *		_channel;
	vector<t_mode>	_modes;
	string			_args;

	void			_addMode(char mode, t_operation op);

	void Mode_Command::changeMode_i(t_operation op);
	void Mode_Command::changeMode_t(t_operation op);
	void Mode_Command::changeMode_k(t_operation op);
	void Mode_Command::changeMode_o(t_operation op);
  
	bool			_fillModeVector(string modes);
	


public:
	Mode_Command(string msg, Server &server, User *sender);
	~Mode_Command();

	bool parse();
	void execute();
};


#endif