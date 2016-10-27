#ifndef HG_FESHELL_CUSTOM_LAYER_READER_WRITER_H
#define HG_FESHELL_CUSTOM_LAYER_READER_WRITER_H

#include <FeShell/Export.h>

#include <osgEarth/XmlUtils>

namespace FeShell
{
	/**
	* @class CCustomLayerReaderWriter
	* @brief �û��Զ���ͼ�����õĶ�ȡ
	* @note ���ڶ��û��Զ����ͼ��������ļ����ж�д����
	* @author c00005
	*/
	class FESHELL_EXPORT CCustomLayerReaderWriter
	{
	public:
		CCustomLayerReaderWriter();

		~CCustomLayerReaderWriter();

	public:
		/**
		*@note: �������������������
		*/
		void AppendConfig(osgEarth::Config config);

		/**
		*@note: ��ָ����·���ж�ȡ�û��Զ���ͼ�������
		*/
		osgEarth::Config Load(std::string strPath);

		/**
		*@note: ���û��Զ����ͼ�㱣�浽ָ���������ļ���
		*/
		bool Save(std::string strPath);

	protected:
		osgEarth::Config	m_rootConfig;
	};
}

#endif//HG_FESHELL_CUSTOM_LAYER_READER_WRITER_H
