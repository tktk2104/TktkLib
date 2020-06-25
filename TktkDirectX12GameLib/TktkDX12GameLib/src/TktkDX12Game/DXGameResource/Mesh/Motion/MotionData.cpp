#include "TktkDX12Game/DXGameResource/Mesh/Motion/MotionData.h"

#include <TktkFileIo/lodevmd.h>

namespace tktk
{
    MotionData::MotionData(const std::string& motionFileName)
    {
        lodevmd::loadData outData{};

        lodevmd::load(&outData, motionFileName);

        for (const auto& node : outData.motionData)
        {
            m_boneKeyFrames[node.boneName].push_back({ node.frameNo, node.location, tktkMath::vec3One, node.rotation });
        }
    }

    std::vector<MotionBoneParam> MotionData::calculateBoneTransformMatrices(unsigned int frame)
    {
        std::vector<MotionBoneParam> result{};
        result.reserve(m_boneKeyFrames.size());

        // モーションに登録されているボーンの種類だけ巡回
        for (const auto& keyFrames : m_boneKeyFrames)
        {
            // 現在のフレームに対応したキーフレームを求める
            auto keyFrame = calculateKeyFrame(keyFrames.second, frame);

            // キーフレームの座標変換を行列にまとめる
            auto transformMat
                = tktkMath::Matrix4::createScale(keyFrame.scale)
                * tktkMath::Matrix4::createFromQuaternion(keyFrame.rotation)
                * tktkMath::Matrix4::createTranslation(keyFrame.position);

            result.push_back({ keyFrames.first, transformMat });
        }
        return result;
    }

    MotionData::KeyFrame MotionData::calculateKeyFrame(const std::vector<MotionData::KeyFrame, std::allocator<MotionData::KeyFrame>>& keyFrames, unsigned int frame)
    {
        // 始まりのインデックス
        unsigned int startKey   = 0;
        // 終わりのインデックス
        unsigned int endKey     = static_cast<int>(keyFrames.size() - 1);

        // もしも現在のフレームが始まりのキーのフレームよりも前であれば
        if (keyFrames.at(startKey).frameNo >= frame)
        {
            // 始まりのキーフレームを返す
            return keyFrames.at(startKey);
        }

        // もしも現在のフレームが終わりのキーのフレームよりも後であれば
        if (keyFrames.at(endKey).frameNo <= frame)
        {
            // 終わりのキーフレームを返す
            return keyFrames.at(endKey);
        }

        // 始まりのインデックスに１を足した数が終わりのインデックスよりも小さい限りループ
        while ((startKey + 1) < endKey)
        {
            // 始まりと終わりのインデックスの中間点を求める
            const unsigned int mid = (startKey + endKey) / 2;

            // もしも現在のフレームが中間のキーのフレームと一緒であれば
            if (keyFrames.at(mid).frameNo == frame)
            {
                // そのフレームを返す
                return keyFrames.at(mid);
            }
            // もしも現在のフレームが中間のキーのフレームよりも後であれば
            else if (keyFrames.at(mid).frameNo < frame)
            {
                // この後巡回する範囲を中間から後ろにする
                startKey = mid;
            }
            // もしも現在のフレームが中間のキーのフレームよりも前であれば
            else
            {
                // この後巡回する範囲を中間から前にする
                endKey = mid;
            }
        }
        
        // 補完に使用するキー
        const auto& firstKey    = keyFrames.at(startKey);
        const auto& secondKey   = keyFrames.at(endKey);

        // 補完に使用する割合
        float amount = static_cast<float>(frame - firstKey.frameNo) / static_cast<float>(secondKey.frameNo - firstKey.frameNo);

        // 補完の計算
        MotionData::KeyFrame result{};
        result.frameNo = frame;
        result.scale    = tktkMath::Vector3::lerp(firstKey.scale, secondKey.scale, amount);
        result.rotation = tktkMath::Quaternion::slerp(firstKey.rotation, secondKey.rotation, amount);
        result.position = tktkMath::Vector3::lerp(firstKey.position, secondKey.position, amount);

        return result;
    }
}