#include <string>

namespace Spreadsheet {

	class Spreadsheet {

	public:
		Spreadsheet(std::string name);

		std::string getName();
		void setName(std::string newName);

	private:
		std::string m_name;

	};

}