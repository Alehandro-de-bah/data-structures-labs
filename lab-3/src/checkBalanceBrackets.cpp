#include "checkBalanceBrackets.h"
#include "StackArray.h"

bool checkBalanceBrackets(const char* text, const int maxDeep)
{
	if (text == nullptr || text[0] == '\0')
	{
		std::cerr << TEXT_IS_EMPTY << std::endl;
		return false;
	}
	if (maxDeep <= 0)
	{
		std::cerr << INCORRECT_MAX_DEEP << std::endl;
		return false;
	}
	StackArray<char> stack(maxDeep);
	for (int i = 0; text[i] != '\0'; i++)
	{
		if (text[i] == '(' || text[i] == '[' || text[i] == '{')
		{
			if (stack.size() >= maxDeep)
			{
				std::cerr << MAXIMUM_DEPTH_OF_BRACKETS << std::endl;
				return false;
			}
			stack.push(text[i]);
		}
		else if (text[i] == ')' || text[i] == ']' || text[i] == '}')
		{
			if (stack.isEmpty())
			{
				std::cerr << UNNECESSARY_CLOSING_BRACKET << std::endl;
				return false;
			}
			char top = stack.pop();
			bool areRoundBrackets = (top == '(' && text[i] == ')');
			bool areSquareBrackets = (top == '[' && text[i] == ']');
			bool areCurlyBrackets = (top == '{' && text[i] == '}');
			if (!areRoundBrackets && !areSquareBrackets && !areCurlyBrackets)
			{
				std::cerr << DIFFERENT_TYPES_OF_BRACKETS << std::endl;
				return false;
			}
		}
	}
	if (stack.isEmpty())
	{
		return true;
	}
	else
	{
		std::cerr << CLOSING_BRACKET_WAS_MISSED << std::endl;
		return false;
	}
}