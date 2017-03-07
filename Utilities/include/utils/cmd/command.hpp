#ifndef UTILS_CMD_COMMAND_HEADER_INCLUDED
#define UTILS_CMD_COMMAND_HEADER_INCLUDED

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <system_error>

#include <boost/noncopyable.hpp>

#include "errorcategory.h"

namespace
{
	void CheckStreamValidity(const std::istream& stream)
	{
		if (stream.fail())
			throw std::system_error(utils::cmd::Error::INVALID_INPUT_FORMAT);
		else if (!stream)
			throw std::system_error(utils::cmd::Error::STREAM_ERROR);
	}
} // namespace

namespace utils
{
namespace cmd
{
	class Command;

	namespace detail
	{
		template <typename... Parameters>
		struct ParseCommandParametersImpl;

		template <typename Parameter, typename... Parameters>
		struct ParseCommandParametersImpl<Parameter, Parameters...>
		{
			static void Parse(std::istream& stream, Command& command)
			{
				Parameter parameter;

				stream >> parameter;
				CheckStreamValidity(stream);

				command.AddParameter(parameter);

				ParseCommandParametersImpl<Parameters...>::Parse(stream, command);
			}
		};

		template <>
		struct ParseCommandParametersImpl<>
		{
			static void Parse(std::istream& stream, Command& command)
			{
			}
		};

		template <typename ...Parameters>
		void ParseCommandParameters(std::istream& stream, Command& command)
		{
			ParseCommandParametersImpl<Parameters...>::Parse(stream, command);
		}
	} // namespace detail

	class Command
	{
	private:
		class Parameter
		{
		public:
			virtual ~Parameter() {}
			virtual void* Get() noexcept = 0;
			virtual Parameter* Clone() const noexcept = 0;
		};

		template<typename ParameterType>
		class ParameterImpl :
			public Parameter
		{
		private:
			ParameterType parameter;

		public:
			ParameterImpl(const ParameterType& parameter) :
				parameter(parameter)
			{
			}

			void* Get() noexcept override
			{
				return &parameter;
			}

			Parameter* Clone() const noexcept override
			{
				return new ParameterImpl(*this);
			}
		};

		std::vector<Parameter*> parameters;

	public:
		std::string command;

		~Command() noexcept
		{
			for (auto* const parameter : parameters)
			{
				delete parameter;
			}
		}

		Command()
		{
		}

		Command(const Command& other) :
			command(other.command)
		{
			for (const auto* const parameter : other.parameters)
			{
				parameters.emplace_back(parameter->Clone());
			}
		}

		Command& operator=(const Command& other)
		{
			command = other.command;

			for (const auto* const parameter : other.parameters)
			{
				parameters.emplace_back(parameter->Clone());
			}

			return *this;
		}

		unsigned int GetAmountOfParameters() const noexcept
		{
			return parameters.size();
		}

		template <typename ParameterType>
		void AddParameter(ParameterType parameter)
		{
			parameters.emplace_back(new ParameterImpl<ParameterType>(parameter));
		}

		template <typename T>
		T& GetParameter(const unsigned int index) const
		{
			return *static_cast<T* const>(parameters.at(index)->Get());
		}
	}; // class Command

	template <typename ...Parameters>
	Command ParseCommand(std::istream& stream)
	{
		Command command;

		// Get the command.
		std::getline(stream, command.command, ' ');
		CheckStreamValidity(stream);

		// Recursively get the parameters.
		detail::ParseCommandParameters<Parameters...>(stream, command);

		return command;
	}

	template <typename ...Parameters>
	Command ParseCommand(std::istream& stream, std::error_code& errorBuffer)
	{
		try
		{
			return ParseCommand<Parameters...>(stream);
		}
		catch (std::system_error exception)
		{
			errorBuffer = exception.code();
		}
	}
} // namespace cmd
} // namespace utils

#endif // #ifndef UTILS_CMD_COMMAND_HEADER_INCLUDED
