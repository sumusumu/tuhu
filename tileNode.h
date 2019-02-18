
//Ÿ�� �ϳ��� ������� 32 x 32
#define TILESIZE 32

#define TILEX 20
#define TILEY 20

//Ÿ���� x���� �� ������
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

#define SAMPLETILEX 20
#define SAMPLETILEY 9

//������ �Ӽ��ο��� ��Ʈ�ʵ�(��� ���� �Ƚᵵ �Ǵµ� �õ��� ������� ���� �����ִٰ� Ī������ �� _��)
#define ATTR_UNMOVAL	0x00000001	//������ ����
#define ATTR_POISON  0x00000002	//������
#define ATTR_SWAMP	0x00000004	//������

//����
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

//������Ʈ
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS, OBJ_FLAG1,
	OBJ_FLAG2, OBJ_TANK1, OBJ_TANK2, OBJ_NONE
};

//������
enum POS
{
	POS_FLAG1, POS_FLAG2, POS_TANK1, POS_TANK2
};

//Ÿ�� ������ ���� ����ü
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

//���ÿ��� �׷��� Ÿ������
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//���� Ÿ�������� ���� ����ü
struct tagCurrentTile
{
	int x;
	int y;
};