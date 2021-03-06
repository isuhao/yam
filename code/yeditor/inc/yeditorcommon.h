#ifndef Y_EDITORCOMMON_H
#define Y_EDITORCOMMON_H

#include <json.h>
#include <yam.h>

#define YEDITOR_NAME                    "Yam Editor"


#define YEDITOR_DELETE(_Object_Ptr)     if (NULL != _Object_Ptr)\
    {\
        delete _Object_Ptr;\
        _Object_Ptr = NULL;\
    }

extern yam::base::YCTree                    gs_FileTreeData;

class YCQUiItem;
class YCQUiTreeItem;

enum EImageType
{
    eImageType_Normal,
    eImageType_Hover,
    eImageType_Pressed,
    eImageType_Disable,
    eImageType_Checked,
    eImageType_Unchecked,
    eImageType_Max,
};

enum ERelationshipType
{
    eRelationshipType_None,
    eRelationshipType_Res,
    eRelationshipType_Ui,
};

typedef struct tagRelationship
{
    ERelationshipType   _eType;
    YCQUiItem*          _pUiItem;
    YCQUiTreeItem*      _pTreeItem;
} SRelationship;

typedef std::map<yam::ystring, SRelationship>    ymnamerelationship;

extern ymnamerelationship                   gs_mRelationship;

typedef struct tagConfigCreateWidget
{
    yam::ystring     _sId;
} SConfigCreateWidget;

typedef struct tagConfigAsset
{
    yam::ystring    _sFile;
    yam::ystring    _sName;
    yam::ystring    _sType;
} SConfigAsset;
typedef std::vector<SConfigAsset>      yvconfigasset;

typedef struct tagConfigScene
{
    yam::ystring    _sLogic;
    yam::YVec2D     _stSize;
    yvconfigasset  _vAssets;
} SConfigScene;

typedef struct tagConfigLayout
{
    yam::ystring    _sType;
    yam::ystring    _sValue;
} SConfigLayout;

#endif // Y_EDITORCOMMON_H
