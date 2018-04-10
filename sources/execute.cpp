/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 16:01:18 by acottier          #+#    #+#             */
/*   Updated: 2018/04/10 16:17:03 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <stack>
#include "../includes/Error.class.hpp"
#include "../includes/Token.class.hpp"
#include "../includes/Operand.class.hpp"

void			getExecOperands(std::stack<IOperand const *> stack, IOperand const **v1, IOperand const **v2, Error & errMsg)
{
	if (stack.empty())
		errMsg.addMsg("Error: couldn't find enough operands.");
	else
	{
		v1 = &stack.top();
		stack.pop();
		if (stack.empty())
			errMsg.addMsg("Error: couldn't find enough operands.");
		else
		{
			v2 = &stack.top();
			stack.pop();
		}
	}
	if (!errMsg.isEmpty())
		throw errMsg;
}

std::string		getExecValue(std::string const & arg)
{
	return (arg.substr(arg.find('('), arg.find(')', arg.find('('))));
}

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

void			opPush(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg)
{
	(void)errMsg;
	Factory	factory;

	stack.push(factory.createOperand(getExecValue(arg), getExecType(arg)));
}

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

void 			opAssert(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg)
{
	eOperandType	assertType = getExecType(arg);
	std::string		assertValue = getExecValue(arg);

	if (stack.empty() || stack.top()->getType() != assertType || assertValue.compare(stack.top()->toString()) != 0)
	{
		errMsg.addMsg("Error: assert failed.");
		throw errMsg;
	}
}

void			opAdd(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg)
{
	(void)arg;
	IOperand	const *v1;
	IOperand	const *v2;
	Factory		factory;

	getExecOperands(stack, &v1, &v2, errMsg);
	stack.push(*v1 + *v2);
}

void			opSub(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg)
{
	(void)arg;
	IOperand	const *v1;
	IOperand	const *v2;
	Factory		factory;

	getExecOperands(stack, &v1, &v2, errMsg);
	stack.push(*v1 - *v2);
}

void			opMul(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg)
{
	(void)arg;
	IOperand	const *v1;
	IOperand	const *v2;
	Factory		factory;

	getExecOperands(stack, &v1, &v2, errMsg);
	stack.push(*v1 * *v2);
}

void			opDiv(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg)
{
	(void)arg;
	IOperand	const *v1;
	IOperand	const *v2;
	Factory		factory;

	getExecOperands(stack, &v1, &v2, errMsg);
	stack.push(*v1 / * v2);
}

void			opMod(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg)
{
	(void)arg;
	IOperand	const *v1;
	IOperand	const *v2;
	Factory		factory;

	getExecOperands(stack, &v1, &v2, errMsg);
	stack.push(*v1 % *v2);
}

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
	std::cout << atoi(stack.top()->toString().c_str()) << std::endl;
}

void			opExit(std::stack<IOperand const *> & stack, std::string const & arg, Error & errMsg) 
{
	(void)stack;
	(void)arg;
	(void)errMsg;
}

void			execute(std::stack<IOperand const *> & stack, std::list<Token *>::iterator ii, Error & errMsg)
{
	std::map<std::string const &, void (*) (std::stack<IOperand const *>, std::string const &, Error &)> functionMap = 
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

	functionMap[(*ii)->getContent()](stack, (*(ii++))->getContent(), errMsg);
}

void			walkthrough(std::list<Token *> input, Error & errMsg)
{
	std::string				cmd;
	std::stack<IOperand const *>	stack;

	for (std::list<Token *>::iterator ii = input.begin() ; ii != input.end() ; ii++ )
	{
		if ((*ii)->getInputType() == INSTRUCTION)
		{
			cmd = (*ii)->getContent();
			if (cmd.compare("push") || cmd.compare("assert"))
			{
				execute(stack, ii, errMsg);
				ii++;
			}
			else
				execute(stack, ii, errMsg);
		}
	}
}