#ifndef SEHLL_CONTOUR_READER_WRITER_H
#define SEHLL_CONTOUR_READER_WRITER_H

#include <FeShell/Export.h>
#include <FeUtils/tinyXml/tinyxml.h>
#include <FeUtils/tinyXml/tinyutil.h>

#include <string>
#include <map>

#include <osg/Array>

namespace FeShell
{
    /**
    * @class CContourConfigModule
    * @brief ѣ��ͼ��������Ϣ
    * @author c00005
    */
    class FESHELL_EXPORT CContourConfig
	{
	public:
		//ѣ��ͼ��Key�Լ���Ӧ�����Խ����ļ����ļ��� 
		typedef std::map<std::string, std::string> ContourMap;

    public:
        CContourConfig();
        ~CContourConfig();

    public:
		bool Valid();
		void SetValid(bool bValue);

		void SetContourList(std::string strKey, std::string strValue);
		void DeleteContourList(std::string strKey);
		ContourMap GetContourList();

		std::string GetDefContour();
		void SetDefContour(std::string strContour);

	private:
		bool                        m_bValid;           //�Ƿ�Ϸ�

		std::string					m_strDefContour;
		ContourMap					m_mapContour;
    };
}

namespace FeShell
{
    /**
      * @class CContourCfgReaderWriter
      * @brief ѣ��ͼ���õ����л��Լ������л�
      * @note ���л��Լ������л�ѣ��ͼ���õ���Ϣ
      * @author c00005
    */
	class FESHELL_EXPORT CContourCfgReaderWriter :public FeUtil::TiXmlVisitor
	{
	public:
		CContourCfgReaderWriter();
		~CContourCfgReaderWriter();

		//��ȡ���õĹ���
	public:
		CContourConfig Read(const std::string& strFileName);

		///���Ĭ�ϵ������ļ��µ�������Ϣ
		CContourConfig Read();

	public:
		virtual bool VisitEnter(const FeUtil::TiXmlElement& ele , const FeUtil::TiXmlAttribute* attr);

		bool AcceptContour(const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr);

		//д�����õĹ���
	public:
		bool Write(CContourConfig config);

		bool Write(CContourConfig config, const std::string& strFileName);

	protected:
		CContourConfig      m_configModule; //ϵͳѣ��ͼ����ģ��
	};
	
	/**
      * @class CContourConfigReader
      * @brief ѣ��ͼ�������ɫ�����Ķ�д������
      * @author c00005
    */
	class FESHELL_EXPORT CContourReaderWriter : public FeUtil::TiXmlVisitor
	{
	public:
		CContourReaderWriter();

		~CContourReaderWriter();

		//��ȡ����
	public:
		///���ָ���������ļ�������Ϣ
		osg::Vec4dArray* Read(const std::string& strFileName);

	protected:
		virtual bool VisitEnter(const FeUtil::TiXmlElement& ele , const FeUtil::TiXmlAttribute* attr);

		bool AcceptContour(const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr);


	public:
		bool Write(osg::Vec4dArray* pArray);

		bool Write(osg::Vec4dArray* pArray, const std::string& strFileName);

	protected:
		osg::ref_ptr<osg::Vec4dArray> m_pContourColor; 

	};


}
#endif//SEHLL_CONTOUR_READER_WRITER_H
