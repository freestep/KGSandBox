#ifndef HG_FESHELL_FEATURE_LOADER_H
#define HG_FESHELL_FEATURE_LOADER_H
#include <osgEarth/MapNode>

#include <FeShell/Export.h>

namespace FeShell
{
	/**
	* @class CFeatureLoader
	* @brief ����Ҫ�ؼ�����
	* @note ���������ļ������õĵ���Ҫ��
	* @author l00008
	*/
	class CFeatureLoader
	{
	public:
		CFeatureLoader(const std::string& strFile, osgEarth::MapNode* pMapNode );

		virtual ~CFeatureLoader();

	public:
		/**
		*@note: ���ص���Ҫ���ļ���ͨ��ָ������Ҫ�������ļ�·��
		*/
		bool Load();

	protected:
		bool Load(std::istream& in, const osgDB::Options* options );

		void CreateFeature(osgEarth::Config& conf);

	protected:
		std::string    m_strFileName;   //�ļ�����
		osgEarth::MapNode*    m_pMapNode; //ͼ���ļ�
	};
}

#endif//HG_FESHELL_FEATURE_LOADER_H
