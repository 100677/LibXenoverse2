#include "ESK.h"

#ifndef LIBXENOVERSE_EAN_H_INCLUDED
#define LIBXENOVERSE_EAN_H_INCLUDED

#define LIBXENOVERSE_EAN_SIGNATURE    "#EAN"

#define LIBXENOVERSE_EAN_KEYFRAMED_ANIMATION_FLAG_POSITION  1792
#define LIBXENOVERSE_EAN_KEYFRAMED_ANIMATION_FLAG_ROTATION  1793
#define LIBXENOVERSE_EAN_KEYFRAMED_ANIMATION_FLAG_SCALE     1794

namespace LibXenoverse
{


class EANAnimation;





/***************************** class EANKeyframe ***************************************/
class EANKeyframe
{
public:
	unsigned int frame;
	float x;
	float y;
	float z;
	float w;

	EANKeyframe(unsigned int frame = 0, float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
	EANKeyframe(EANKeyframe *source);
	
	void read(File *file, unsigned char keyframe_size);
	void write(File *file, unsigned char keyframe_size);
	void readFrame(File *file, unsigned char index_size);
	void writeFrame(File *file, unsigned char index_size);

	unsigned int &getFrame() { return frame; }
	void setFrame(unsigned int value) { frame = value; }
	void setXYZW(float x, float y, float z, float w);

	void operator=(EANKeyframe &source);


	bool	importXml(TiXmlElement* xmlCurrentNode);
	TiXmlElement*	exportXml(void);
};






/***************************** class EANKeyframedAnimation ***************************************/
class EANKeyframedAnimation
{
	friend class EmaCommand;
	friend class EmaAnimation;

protected:
	unsigned int flag;
	vector<EANKeyframe> keyframes;

public:
	EANKeyframedAnimation(unsigned int flag = 0) { this->flag = flag; }
	EANKeyframedAnimation(EANKeyframedAnimation *source);

	vector<EANKeyframe> &getKeyframes(){ return keyframes; };

	void read(File *file, unsigned char index_size, unsigned char keyframe_size);
	size_t write(File *file, unsigned char index_size, unsigned char keyframe_size);

	void getInterpolatedFrame(unsigned int frame, float &x, float &y, float &z, float &w);
	void getFrame(EANKeyframe *keyframe, float &x, float &y, float &z, float &w);

	unsigned int getFlag() { return flag; }
	void setFlag(unsigned int flag) { this->flag = flag; }

	void operator=(EANKeyframedAnimation &source);


	bool	importXml(TiXmlElement* xmlCurrentNode);
	TiXmlElement*	exportXml(void);


#ifdef LIBXENOVERSE_FBX_SUPPORT
	bool importFBXPositionAnimCurve(FbxNode *fbx_node, size_t nbframes, FbxAnimCurve* fbx_animCurve_translation_x, FbxAnimCurve* fbx_animCurve_translation_y, FbxAnimCurve* fbx_animCurve_translation_z);
	bool importFBXRotationAnimCurve(FbxNode *fbx_node, size_t nbframes, FbxAnimCurve* fbx_animCurve_rotation_x, FbxAnimCurve* fbx_animCurve_rotation_y, FbxAnimCurve* fbx_animCurve_rotation_z);
	bool importFBXScalingAnimCurve(FbxNode *fbx_node, size_t nbframes, FbxAnimCurve* fbx_animCurve_scale_x, FbxAnimCurve* fbx_animCurve_scale_y, FbxAnimCurve* fbx_animCurve_scale_z);

protected:
	void mergeListTime(FbxAnimCurve* fbx_animCurve, std::vector<FbxTime> &list_fbxtime);
	float getValueForTime(FbxAnimCurve* fbx_animCurve, FbxTime fbxtime, size_t &currentIndex, size_t nbFrames, float defaultValue);
#endif
};





/***************************** class EANAnimationNode ***************************************/
class EANAnimationNode
{
	friend class EmaAnimation;

protected:
	unsigned short bone_index;
	vector<EANKeyframedAnimation> keyframed_animations;
	

public:
	EANAnimationNode() { this->bone_index = 0; }
	EANAnimationNode(EANAnimationNode *source);

	vector<EANKeyframedAnimation> &getKeyframed_animations(){ return keyframed_animations; }

	void read(File *file, unsigned char index_size, unsigned char keyframe_size);
	size_t write(File *file, unsigned char index_size, unsigned char keyframe_size);

	unsigned int getBoneIndex() { return bone_index; }
	void	setBoneIndex(unsigned int index) { bone_index = index; }

	bool haveKeyFrameAnimation(unsigned int flag);
	bool getInterpolatedFrame(unsigned int frame, unsigned int flag, float &x, float &y, float &z, float &w);
	void addTPoseAnimation(void);

	void operator=(EANAnimationNode &source);


	bool	importXml(TiXmlElement* xmlCurrentNode, ESK* esk);
	TiXmlElement*	exportXml(ESK* esk);

#ifdef LIBXENOVERSE_FBX_SUPPORT
	size_t importFBXAnimationCurves(FbxNode *lNode, FbxAnimLayer* lAnimLayer, size_t boneIndex);
#endif
};

class EAN;




/***************************** class EANAnimation ***************************************/
class EANAnimation
{
	friend class EmaAnimation;

protected:
	string name;
	unsigned int frame_count;
	unsigned char frame_index_size;									//some code into ema file suppose there also have some bit of this for increase the nbBytes for "frame" //todo check that.
	unsigned char frame_float_size;
	EAN *parent;
	vector<EANAnimationNode> nodes;

	std::vector<string> mListFilenameOrigin;

public:
	EANAnimation(EAN *v = NULL);
	EANAnimation(EANAnimation *source, EAN *v = NULL);
	EANAnimation(EANAnimation *source, vector<string> &listBoneFilterNames, EAN *v = NULL);			//version with a bone filter

	unsigned char	getFrame_index_size(void){ return frame_index_size; }
	unsigned char	getFrame_float_size(void){ return frame_float_size; }

	void	setParent(EAN *v) {parent = v; }
	EAN*	getParent(void) { return parent; }
		

	void	read(File *file);
	void	readName(File *file);
	size_t	write(File *file);
	void	writeName(File *file);

	unsigned int	getFrameCount(void) { return frame_count; }
	void	setFrameCount(unsigned int value) { frame_count = value; }

	string	getName(void) { return name; }
	void	setName(string newName){ name = newName; }
	vector<EANAnimationNode>	&getNodes(void) { return nodes; }
	unsigned char	&getFrameIndexSize(void) { return frame_index_size; }
	unsigned char	&getFrameFloatSize(void) { return frame_index_size; }
	string	getFilenameOriginList_str(void);
	std::vector<string>	&getFilenameOriginList(void) { return mListFilenameOrigin; }

	void copy(EANAnimation &source, bool keepName = true);
	void copy(EANAnimation &source, vector<string> &listBoneFilterNames, bool keepName = true);
		
	void	changeBoneIndexes(const std::vector<std::vector<size_t>> &listMovingindex);
	void	addBoneAnimationFromAnotherEan(EANAnimation &ean_Anim_src, std::vector<std::vector<size_t>> &listRelationIndex, bool matchDuration);
	void	addTPoseAnimation(ESK* skeleton);

	void operator=(EANAnimation &source);


	bool	importXml(TiXmlElement* xmlCurrentNode, EAN* eanParent);
	TiXmlElement*	exportXml(void);

#ifdef LIBXENOVERSE_FBX_SUPPORT
	void	importFBXAnimation(FbxScene *scene, FbxAnimStack *lAnimStack, ESK* skeleton);
#endif
};






/***************************** class EAN ***************************************/
class EAN
{
	friend class EMA;

protected:
	string name;
	unsigned int unknown_total;
	ESK* skeleton;
	vector<EANAnimation> animations;

public:
	EAN(void) { name = ""; skeleton = NULL; unknown_total = 0; }
	virtual ~EAN(void);

	bool	load(string filename);
	void	save(string filename, bool big_endian = false);

	void	read(File *file);
	void	write(File *file);

	void	merge(EAN *ean);

	string	getName(void) { return name; }
	void	setSkeleton(ESK* skel) { skeleton = skel; }
	ESK*	getSkeleton(void){ return skeleton; }
	vector<EANAnimation>	&getAnimations(void) { return animations; }

	void	changeBoneIndexes(const std::vector<std::vector<size_t>> &listMovingindex);
	void	addBoneAnimationFromAnotherEan(EAN* ean_src, std::vector<std::vector<size_t>> &listRelationIndex, bool matchDuration);
	void	addTPoseAnimation(void);

	bool	loadXml(string filename);
	void	saveXml(string filename);
	bool	importXml(TiXmlElement* xmlCurrentNode);
	TiXmlElement*	exportXml(void);

#ifdef LIBXENOVERSE_FBX_SUPPORT
	void	importFBXAnimations(FbxScene *scene, std::vector<FbxAnimStack *> list_AnimStack);
	vector<FbxAnimCurveNode *>  exportFBXAnimations(FbxScene *scene, std::vector<FbxAnimStack *> list_AnimStack, ESK::FbxBonesInstance_DBxv* fbxBoneInst);

	FbxAnimCurveNode *createFBXAnimationCurveNode(FbxNode *fbx_node, EANAnimation *animation, EANAnimationNode* anim_node, FbxAnimStack *lAnimStack, FbxAnimLayer* lAnimLayer);
#endif
};

}

#endif