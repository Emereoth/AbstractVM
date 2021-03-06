/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 16:01:18 by acottier          #+#    #+#             */
/*   Updated: 2018/04/24 14:36:11 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <stack>
#include "../includes/Error.class.hpp"
#include "../includes/Token.class.hpp"
#include "../includes/Operand.class.hpp"

enum eOperationType
{
	ADD,
	SUB,
	MUL,
	DIV,
	MOD
};

/*
*	Pops two operands from the top of the stack and pushes the operation result
*/
void			doOp(std::stack<IOperand const *> &stack, eOperationType type, Error & errMsg)
{
	if (stack.size() > 1)
	{
		IOperand const *v1 = stack.top();
		stack.pop();
		IOperand const *v2 = stack.top();
		stack.pop();
		switch (type)
		{
			case ADD:
			{
				stack.push(*v2 + *v1);
				break;
			}
			case SUB:
			{
				stack.push(*v2 - *v1);
				break;
			}
			case MUL:
			{
				stack.push(*v2 * *v1);
				break;
			}
			case DIV:
			{
				stack.push(*v2 / *v1);
				break;
			}
			case MOD:
			{
				stack.push(*v2 % *v1);
				break;
			}
		}
		delete v1;
		delete v2;
	}
	else
	{
		errMsg.addMsg("Error: couldn't find enough operands for asked operation.");
		throw errMsg;
	}
}

/*
*	Returns the value from 'push' or 'assert' parameter
*/
std::string		getExecValue(std::string const & arg)
{
	return (arg.substr(arg.find('(') + 1, arg.find(')') - arg.find('(') - 1));
}

/*
*	Returns the data type from 'push' or 'assert' parameter
*/
eOperandType	getExecType(std::string const & arg)
{
	std::map<std::string, eOperandType>	typeMap = 
	{
		{"int8", Int8},
		{"int16", Int16},
		{"int32", Int32},
		{"float", Float},
		{"double", Double}
	};
	return (typeMap[arg.substr(0, arg.find('('))]);
}

/*
*	Adds new value on top of the stack
*/
void			opPush(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg)
{
	(void)errMsg;
	Factory	factory;

	stack.push(factory.createOperand(getExecValue(arg), getExecType(arg)));
}

/*
*	Deletes top value on the stack
*/
void			opPop(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg)
{
	(void)arg;
	if (stack.empty())
	{
		errMsg.addMsg("Error: 'pop' on empty stack.");
		throw errMsg;
	}
	stack.pop();
}

/*
*	Displays all of the values on the stack
*/
void			opDump(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg)
{
	(void)arg;
	(void)errMsg;
	std::stack<IOperand const *>	tmpStack = stack;

	while (!tmpStack.empty())
	{
		std::cout << tmpStack.top()->toString() << std::endl;
		tmpStack.pop();
	}
}

/*
*	Checks if top value on stack is identical (in value AND type) to the one passed as parameter
*/
void 			opAssert(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg)
{
	eOperandType	assertType = getExecType(arg);
	std::string		assertValue = getExecValue(arg);

	if (stack.empty() || stack.top()->getType() != assertType || assertValue.compare(stack.top()->toString()) != 0)
	{
		errMsg.addMsg("Error: assert failed.");
		if (!stack.empty() && stack.top()->getType() != assertType)
			std::cout << "Incorrect type" << std::endl;
		if (!stack.empty() && assertValue.compare(stack.top()->toString()) != 0)
			std::cout << "Incorrect value" << std::endl;
		throw errMsg;
	}
}

/*
*	Addition operation
*/
void			opAdd(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg)
{
	(void)arg;
	
	doOp(stack, ADD, errMsg);
}

/*
*	Substraction operation
*/
void			opSub(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg)
{
	(void)arg;
	
	doOp(stack, SUB, errMsg);
}

/*
*	Multiplication operation
*/
void			opMul(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg)
{
	(void)arg;
	
	doOp(stack, MUL, errMsg);
}

/*
*	Division operation
*/
void			opDiv(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg)
{
	(void)arg;
	
	doOp(stack, DIV, errMsg);
}

/*
*	Modulo operation
*/
void			opMod(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg)
{
	(void)arg;
	
	doOp(stack, MOD, errMsg);
}

/*
*	Asserts top value on stack is of type Int8 an then prints its corresponding ASCII character
*/
void			opPrint(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg)
{
	(void)arg;
	if (stack.empty())
	{
		errMsg.addMsg("Error: print on empty stack.");
		throw errMsg;
	}
	if (stack.top()->getType() != Int8)
	{
		errMsg.addMsg("Error: top value on stack is not in a printable format.");
		throw errMsg;
	}
	std::cout << (char)atoi(stack.top()->toString().c_str()) << std::endl;
}

/*
*	Does nothing, the exit condition relative to this command is handled in walkthrough()
*/
void			opExit(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg) 
{
	(void)stack;
	(void)arg;
	(void)errMsg;
}

/*
*	Calls appropriate command function
*/
void			execute(std::stack<IOperand const *> & stack, std::list<Token *>::iterator ii, Error & errMsg)
{
	std::map<std::string const , void (*) (std::stack<IOperand const *> &, std::string const &, Error &)> functionMap = 
	{
		{"push", &opPush},
		{"pop", &opPop},
		{"dump", &opDump},
		{"assert", &opAssert},
		{"add", &opAdd},
		{"sub", &opSub},
		{"mul", &opMul},
		{"div", &opDiv},
		{"mod", &opMod},
		{"print", &opPrint},
		{"exit", &opExit}
	};
	std::list<Token *>::iterator	next = ii;
	
	if (!(*ii)->getContent().compare("push") || !(*ii)->getContent().compare("assert"))
		next++;
	functionMap[(*ii)->getContent()](stack, (*next)->getContent(), errMsg);
}

/*
*	Advances through instruction list
*/
void			walkthrough(std::list<Token *> input, Error & errMsg)
{
	std::string						cmd;
	std::stack<IOperand const *>	stack;

	for (std::list<Token *>::iterator ii = input.begin() ; ii != input.end() ; ii++ )
	{
		if ((*ii)->getInputType() == INSTRUCTION)
		{
			cmd = (*ii)->getContent();
			execute(stack, ii, errMsg);
			if	(!cmd.compare("exit"))
				break; 
		}
	}
	while (!stack.empty())
	{
		delete stack.top();
		stack.pop();
	}

}