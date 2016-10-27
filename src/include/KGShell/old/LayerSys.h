/**************************************************************************************************
* @file LayerSys.h
* @note ��Ҫ��װ��ͼ��ģ��
* @author l00008
* @data 2014-7-19
**************************************************************************************************/
#ifndef HG_LAYER_SYSTEM_CALL_H
#define HG_LAYER_SYSTEM_CALL_H

#include <osgEarth/ImageLayer>
#include <osgEarth/ElevationLayer>
#include <osgEarth/ModelLayer>
#include <osgEarth/TerrainEffect>

#include <FeShell/Export.h>
#include <FeUtils/SceneSysCall.h>

namespace FeShell
{
	/**
	* @class CFeEffectLayer
	* @brief ��Чͼ��
	* @note ��װ��Чͼ�㣬�ṩ��Чͼ�����ʾ�����ز���
	* @author l00008
	*/
	class FESHELL_EXPORT CFeEffectLayer : public osgEarth::Layer
	{
	public:
		CFeEffectLayer();
		CFeEffectLayer(
			osgEarth::TerrainEffect* pEffectLayer, 
			osgEarth::TerrainEngineNode* pTerrainNode, 
			const std::string& strName,
			bool bVisible);
		virtual ~CFeEffectLayer();

	public:
		/**
		*@note: ��������״̬
		*/
		void setVisible(bool bVisible);
		bool getVisible() const;

		/**
		*@note: ������Ҫ��װ��osgEarthEfect
		*/
		void SetEffectLayer(osgEarth::TerrainEffect* pEffectLayer);

		/**
		*@note: ��÷�װ��osgEarthEfect
		*/
		osgEarth::TerrainEffect* GetEffectLayer();

		/**
		*@note: ����MapNode
		*/
		void SetTerrainEngineNode(osgEarth::TerrainEngineNode* pTerrainNode);

		/**
		*@note: �������
		*/
		virtual const std::string& getName() const;
		virtual void setName(const std::string& strName);

	protected:
		osg::observer_ptr<osgEarth::TerrainEngineNode>      m_opTerrainNode;
		osg::ref_ptr<osgEarth::TerrainEffect>               m_rpEffectLayer;
		bool                                                m_bVisible;
		std::string                                         m_strName;

	};

	typedef std::vector< osg::ref_ptr<CFeEffectLayer> > EffectLayerVector;
}

namespace FeShell
{
	const std::string LAYER_SYSTEM_CALL_DEFAULT_KEY("LayerSystem");

	/**
	* @class CLayerSys
	* @brief ͼ��ϵͳ
	* @note ͼ��ϵͳ����װ���ͼ����������Ĳ���
	* @author l00008
	*/

	class FESHELL_EXPORT CLayerSys : public FeUtil::CSceneSysCall
	{
	public:
		CLayerSys();

		typedef std::vector< osg::ref_ptr<osgEarth::ModelLayer> > LayerList;

		typedef std::map< std::string, LayerList > LayersLevelMap;
		typedef std::map< int, LayersLevelMap > LayersIndexMap;
		typedef std::map<std::string,LayersIndexMap > LayersTypeMap;

	public:
		/**
		*@note: ���Ӱ��ͼ��
		*/
		void GetImageLayers(osgEarth::ImageLayerVector& vecLayer);

		/**
		*@note: ��õ���ͼ������
		*/
		void GetTerrainLayers(osgEarth::ElevationLayerVector& vecLayer);

		/**
		*@note: ���ģ������ͼ��
		*/
		void GetModelLayers(osgEarth::ModelLayerVector& vecLayer);

		/**
		*@note: ���Shpͼ���ļ����
		*/
		void GetShpLayers(osgEarth::ModelLayerVector& vecLayer);

		/**
		*@note: ���ʸ��ͼ��
		*/
		//void GetVectorLayers(osgEarth::HgLayerVector& vecLayer);

		/**
		*@note: �����Чͼ��
		*/
		void GetEffectLayers(EffectLayerVector& vecLayer);

		template<typename T>
		T* GetEffectLayer() 
		{
			osgEarth::MapNode* pMapNode = m_opRenderContext->GetMapNode();
			if(pMapNode)
			{
				osgEarth::TerrainEngineNode* pEngineNode = pMapNode->getTerrainEngine();
				if(pEngineNode)
				{
					return pEngineNode->getEffect<T>();
				}
			}

			return NULL;
		}

	///��չ�Ľӿڣ���Feature������ʾ
	public:

		/**
		*@note: ���Featureͼ��
		*/
		void GetTypeFLayer(LayersTypeMap &mapTypeLayer);

		/**
		*@note: ���ȫ�ֵ�Feature
		*/
		void GetGlobalFLayer(osgEarth::ModelLayerVector& vecLayer);

	public:
		/**
		*@note: ���һ���߳�ͼ�㣬��������ӵ�ͼ��
		*/
		osgEarth::ElevationLayer* AddElevationLayer(const std::string strPath);

		/**
		*@note: ���һ���߳�ͼ�㣬��������ӵ�ͼ��
		*/
		bool AddElevationLayer(osgEarth::ElevationLayer* pLayer);

		/**
		*@note:ɾ��һ���߳�ͼ��
		*/
		bool DeleteElevationLayer(osgEarth::ElevationLayer* pLayer);

		/**
		*@note: ���һ������ͼƬͼ�㣬��������ӵ�ͼ��
		*/
		osgEarth::ImageLayer* AddImageLayer(const std::string strPath);
		
		/**
		*@note: ���һ������ͼƬͼ�㣬��������ӵ�ͼ��
		*/
		bool AddImageLayer(osgEarth::ImageLayer* pLayer);
		
		/**
		*@note:ɾ��һ���߳�ͼ��
		*/
		bool DeleteImageLayer(osgEarth::ImageLayer* pLayer);

		/**
		*@note: ���һ��ʸ��ͼ�㣬��������ӵ�ͼ��
		*/
		osgEarth::ModelLayer* AddFeatureLayer(const std::string strPath);
				
		/**
		*@note: ���һ��ʸ��ͼ�㣬��������ӵ�ͼ��
		*/
		bool AddFeatureLayer(osgEarth::ModelLayer* pLayer);

		/**
		*@note:ɾ��һ��ʸ��ͼ��
		*/
		bool DeleteFeatureLayer(osgEarth::ModelLayer* pLayer);
			
		/**
		*@note:ɾ��һ��ʸ��ͼ��
		*/
		bool DeleteLayer(osgEarth::Layer* pLayer);

		/**
		*@note: ���һ����ɫ������
		*/
		void AddImageColorFilter(osgEarth::ColorFilter* pColorFilter);

		/**
		*@note: �Ƴ�һ����ɫ������
		*/
		void RemoveImageColorFilter(osgEarth::ColorFilter* pColorFilter);
		void RemoveImageColorFilters();

		/**
		*@note: �ж�һ����ɫ�������Ƿ�ע��
		*/
		//bool IsImageColorInstall(osgEarth::ColorFilter* pColorFilter){};

		///����û����õ�ͼ������·��
		std::string GetCustomConfigPath() const;

		///����û����õ�ͼ������·��
		void SetCustomConfigPath(const std::string& strPath);

		///����û����õĸ߳���ɫ����·��
		std::string GetContourConfigPath() const;

		///����û����õĸ߳���ɫ����·��
		void SetContourConfigPath(const std::string& strPath);

	protected:
		/**
		*@note: ʵ�ֱ�ϵͳģ����Ҫ�ĳ�ʼ���ͷ���ʼ���������˺����ڸ������Ѿ�����
		*/
		virtual bool InitiliazeImplement();
		virtual bool UnInitiliazeImplement();

	protected:
		virtual ~CLayerSys();

		///���Map
		osgEarth::Map* GetMap();

		///�����Ч�б�����ʼ��
		void UpdateEffectLayer();

		///�����ṩ�����͹���ModelLayer�ļ���
		void FilterModelLayes(const std::string& strType, osgEarth::ModelLayerVector& vecLayer);

		///�жϱ�Layer�Ƿ����ƶ������ͣ�����ʹ���ַ�����ʾ
		bool IsType(const std::string& strType, osgEarth::ModelLayer* pLayer);

		void CreateMapLevelLayer(LayersTypeMap &levelMap, const osgEarth::ModelLayerVector& lyerVector);
		
	protected:
		std::string					m_strCustomConfigPath;
		std::string					m_strContourConfigPath;
		EffectLayerVector           m_mapEffectLayer; //������Чͼ�㲻���ͷ�

	};

}



#endif//HG_LAYER_SYSTEM_CALL_H
