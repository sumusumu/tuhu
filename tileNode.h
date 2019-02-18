
//타일 하나의 사이즈는 32 x 32
#define TILESIZE 32

#define TILEX 20
#define TILEY 20

//타일의 x축의 총 사이즈
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

#define SAMPLETILEX 20
#define SAMPLETILEY 9

//지형에 속성부여할 비트필드(요샌 굳이 안써도 되는데 올드한 팀장님은 쓰면 센스있다고 칭찬해줌 ㅋ _ㅋ)
#define ATTR_UNMOVAL	0x00000001	//못가는 지형
#define ATTR_POISON  0x00000002	//독지대
#define ATTR_SWAMP	0x00000004	//늪지대

//지형
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

//오브젝트
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS, OBJ_FLAG1,
	OBJ_FLAG2, OBJ_TANK1, OBJ_TANK2, OBJ_NONE
};

//포지션
enum POS
{
	POS_FLAG1, POS_FLAG2, POS_TANK1, POS_TANK2
};

//타일 정보에 관한 구조체
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

//샘플에서 그려올 타일정보
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//현재 타일정보를 담은 구조체
struct tagCurrentTile
{
	int x;
	int y;
};