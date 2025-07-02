#include <iostream>
#include <vector>
#include <string>
#include <locale> // Добавление библиотеки для работы с локалью
#include <windows.h>




// Структура для хранения данных подразделения
struct Division {
	std::string name;
	double averageStaffCount; // Среднесписочная численность
	double assetCost; // Остаточная стоимость ОС
	double laborCosts; // Расходы на оплату труда
};

// Функция для расчета доли налоговой базы подразделения
double calculateTaxShare(const Division& division, double totalStaffCount, double totalAssetCost) {
	double staffShare = division.averageStaffCount / totalStaffCount;
	double assetShare = division.assetCost / totalAssetCost;
	return (staffShare + assetShare) / 2; // Нормализация
}


int main() {



	SetConsoleCP(1251); // ввод с консоли в Windows-1251
	SetConsoleOutputCP(1251); // вывод в консоль в Windows-1251
	setlocale(LC_ALL, "Russian");

	char continueChoice;
	do {
		system("cls"); // очистка экрана

	std::cout << "Добро пожаловать в калькулятор доли прибыли!\n\n"
		<< "Этот инструмент поможет вам рассчитать долю налоговой базы "
		"для каждого подразделения вашего юридического лица\n\n"
		<< "Чтобы начать работу, вам нужно будет ввести несколько параметров:\n\n"
		<< "1. Название юридического лица.\n"
		<< "2. Отчётный период (1 квартал, полугодие, 9 месяцев или год).\n"
		<< "3. Количество подразделений.\n"
		<< "4. Для каждого подразделения:\n"
		"   * название;\n"
		"   * среднесписочная численность;\n"
		"   * остаточная стоимость основных средств (ОС);\n"
		"   * расходы на оплату труда.\n\n"
		<< "После ввода всех данных программа автоматически рассчитает долю "
		"налоговой базы для каждого подразделения и выведет результаты.\n";

	// Ввод данных о юридическом лице
	std::cout << "\n\nВведите название юридического лица: ";
	std::string companyName;
	std::getline(std::cin, companyName);

	// Выбор отчетного периода
	std::cout << "Выберите отчетный период:\n";
	std::cout << "1 - 1 квартал\n";
	std::cout << "2 - полугодие\n";
	std::cout << "3 - 9 месяцев\n";
	std::cout << "4 - год\n";
	int period;
	std::cin >> period;
	std::cin.ignore(); // Очищаем буфер ввода

	// Ввод количества подразделений
	std::cout << "Введите количество подразделений: ";
	int divisionCount;
	std::cin >> divisionCount;
	if (divisionCount <= 0) {
		std::cout << "Ошибка: количество подразделений должно быть положительным!\n";
		return 1;
	}

	std::cin.ignore(); // Очищаем буфер ввода

	// Инициализация вектора для хранения данных подразделений
	std::vector<Division> divisions(divisionCount);

	// Ввод данных для каждого подразделения
	for (int i = 0; i < divisionCount; ++i) {
		std::cout << "Подразделение " << i + 1 << ":\n";
		std::cout << "Название: ";
		std::getline(std::cin, divisions[i].name);
		std::cout << "Среднесписочная численность: ";
		std::cin >> divisions[i].averageStaffCount;
		if (divisions[i].averageStaffCount <= 0) {
			std::cout << "Ошибка: Среднесписочная численность должна быть положительной!\n";
			return 1;
		}
		std::cout << "Остаточная стоимость ОС: ";
		std::cin >> divisions[i].assetCost;
		if (divisions[i].assetCost <= 0) {
			std::cout << "Ошибка: Остаточная стоимость ОС должна быть положительной!\n";
			return 1;
		}
		std::cout << "Расходы на оплату труда: ";
		std::cin >> divisions[i].laborCosts;
		if (divisions[i].laborCosts <= 0) {
			std::cout << "Ошибка: Расходы на оплату труда должны быть положительными!\n";
			return 1;
		}
		std::cin.ignore(); // Очищаем буфер ввода
	}

	// Расчет общих значений для всех подразделений
	double totalStaffCount = 0;
	double totalAssetCost = 0;
	for (const auto& division : divisions) {
		totalStaffCount += division.averageStaffCount;
		totalAssetCost += division.assetCost;
	}

	// Вывод результатов
	std::cout << "\nРезультаты:\n";
	for (const auto& division : divisions) {
		double taxShare = calculateTaxShare(division, totalStaffCount, totalAssetCost);
		std::cout << "Подразделение: " << division.name << "\n";
		std::cout << "Доля налоговой базы: " << taxShare << "\n\n";
	}
	// Запрос на повторный запуск
	std::cout << "\nХотите выполнить новый расчет? (д/н): ";
	std::cin >> continueChoice;
	std::cin.ignore();

	} while (tolower(continueChoice) == 'д');
	return 0;
}