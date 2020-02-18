#include "TktkDirectX11Wrapper/Graphics/Animation/Asset/AnimationData.h"

#include <stdexcept>
#include <algorithm>

namespace tktk
{
	inline std::pair<int, int> findKeyFrameSegment(const std::vector<KeyFrame>& keys, float frameNo);

	AnimationData::AnimationData(
		const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames
	)
		: m_boneKeyFrames(boneKeyFrames)
	{
	}

	AnimationData::~AnimationData()
	{
	}

	KeyFrame AnimationData::calculateKeyFrame(const std::string & boneName, float frameNo) const
	{
		const auto keys = m_boneKeyFrames.find(boneName);
		KeyFrame result;

		if (keys == m_boneKeyFrames.end())
		{
			throw std::runtime_error("not found boneName");
		}

		const auto& segment = findKeyFrameSegment(keys->second, frameNo);
		if (segment.first == segment.second)
		{
			return keys->second.at(segment.first);
		}
		const auto& first = keys->second.at(segment.first);
		const auto& second = keys->second.at(segment.second);
		const float t = (frameNo - first.frameNo) / (second.frameNo - first.frameNo);
		result.frameNo = frameNo;

		result.scale = Vector3::lerp(first.scale, second.scale, t);
		result.rotate = Quaternion::slerp(first.rotate, second.rotate, t);
		result.position = Vector3::lerp(first.position, second.position, t);

		return result;
	}

	float AnimationData::findEndFrameNo() const
	{
		float result = 0.0f;

		std::for_each(
			std::begin(m_boneKeyFrames),
			std::end(m_boneKeyFrames),
			[&result](const auto& node) { result = std::max(result, node.second.back().frameNo); }
		);
		return result;
	}

	inline std::pair<int, int> findKeyFrameSegment(const std::vector<KeyFrame>& keys, float frameNo)
	{
		int start = 0;
		int end = static_cast<int>(keys.size() - 1);

		if (keys.at(start).frameNo >= frameNo)
		{
			return std::pair<int, int>(start, start);
		}

		if (keys.at(end).frameNo <= frameNo)
		{
			return std::pair<int, int>(end, end);
		}

		while ((start + 1) < end)
		{
			const int mid = (start + end) / 2;

			if (keys.at(mid).frameNo == frameNo)
			{
				return std::pair<int, int>(mid, mid);
			}
			else if (keys.at(mid).frameNo < frameNo)
			{
				start = mid;
			}
			else
			{
				end = mid;
			}
		}
		return std::pair<int, int>(start, end);
	}
}