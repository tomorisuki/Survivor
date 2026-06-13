#pragma once

#include <string>
#include <functional>

#include "FMath.h"

struct UpgradeData
{
	std::string title = "";
	int weight = 0;
	std::function<void()> apply = nullptr;
};


class UpgradePool
{
public:

	void AddUpgradeData(const std::string& title, std::function<void()> apply, int weight = 1)
	{
		UpgradeData data;
		data.title = title;
		data.weight = weight;
		data.apply = std::move(apply);
		buffPool.push_back(data);
	}

	std::vector<UpgradeData> GetThreeUpgradeData()
	{
		std::vector<int> weights;
		std::vector<UpgradeData> pool = buffPool;
		std::vector<UpgradeData> result;

		for (std::size_t i = 0; i < 3; i++) {

			for (auto& buff : pool) {
				weights.push_back(buff.weight);
			}
			std::discrete_distribution<> dist(weights.begin(), weights.end());
			int index = dist(FMath::GetRandomEngine());
			result.push_back(pool[index]);

			pool.erase(pool.begin() + index);
			weights.clear();
		}

		return result;
	}

private:
	std::vector<UpgradeData> buffPool;
};

