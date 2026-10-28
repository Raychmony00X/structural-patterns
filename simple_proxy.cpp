#include <memory>
#include <iostream>

class VeryHeavyDatabase {
public:
	std::string GetData(const std::string& key) const noexcept {
		return "Very Big Data String: " + key;
	}

};

class OneShotDB : public VeryHeavyDatabase {
public:
	explicit OneShotDB(std::unique_ptr<VeryHeavyDatabase>& data_base, int& count) : 
		m_data_base(std::move(data_base)), m_count(count) {}

	std::string GetData(const std::string& key) {
		if (m_count > 0) {
			m_count--;
			return m_data_base->GetData(key);
		}

		return "error";
	}

private:
	std::unique_ptr<VeryHeavyDatabase> m_data_base;
	int m_count;
};

int main() {
	auto data_base = std::make_unique<VeryHeavyDatabase>();
	int limit = 2; 

	auto limited_calls = std::make_unique<OneShotDB>(data_base, limit);

	std::cout << limited_calls->GetData("key") << std::endl;
	std::cout << limited_calls->GetData("key") << std::endl;
	std::cout << limited_calls->GetData("key") << std::endl;

	return 0;
}