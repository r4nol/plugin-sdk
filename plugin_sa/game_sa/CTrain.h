#pragma once
#include "plbase/PluginBase_SA.h"
#include "CVehicle.h"
#include "CDoor.h"
#include "CTrainNode.h"

enum eTrainNodes {
    TRAIN_NODE_NONE = 0,
    TRAIN_DOOR_LF = 1,
    TRAIN_DOOR_RF = 2,
    TRAIN_WHEEL_RF1 = 3,
    TRAIN_WHEEL_RF2 = 4,
    TRAIN_WHEEL_RF3 = 5,
    TRAIN_WHEEL_RB1 = 6,
    TRAIN_WHEEL_RB2 = 7,
    TRAIN_WHEEL_RB3 = 8,
    TRAIN_WHEEL_LF1 = 9,
    TRAIN_WHEEL_LF2 = 10,
    TRAIN_WHEEL_LF3 = 11,
    TRAIN_WHEEL_LB1 = 12,
    TRAIN_WHEEL_LB2 = 13,
    TRAIN_WHEEL_LB3 = 14,
    TRAIN_BOGIE_FRONT = 15,
    TRAIN_BOGIE_REAR = 16,
    TRAIN_NUM_NODES
};

class CTrain : public CVehicle {
protected:
    CTrain(plugin::dummy_func_t) : CVehicle(plugin::dummy) {}
public:
    short             m_nNodeIndex;
    char _pad1[2];
    float             m_fTrainSpeed;
    float             m_fCurrentRailDistance;
    float             m_fLength;
    int field_5B0;
    int field_5B4;
    struct {
        unsigned char unknown1 : 1;
        unsigned char unknown2 : 1;
        unsigned char bIsStreak : 1;
        unsigned char bIsFrontCarriage : 1;
        unsigned char bIsLastCarriage : 1;
        unsigned char bMissionTrain : 1;
        unsigned char bClockwiseDirection : 1;
        unsigned char unknown8 : 1;
    } m_nTrainFlags;
    struct {
        unsigned char bDerailed : 1;
    } m_nWreckingFlags;
    char field_5BA[2];
    int field_5BC;
    char              m_nTrackId;
    char field_5C1;
    short field_5C2;
    int               m_nTimeCreated;
    short field_5C8;
    char field_5CA;
    unsigned char     m_nPassengerFlags;
    CPed             *m_pPassenger;
    CTrain           *m_pPrevCarriage;
    CTrain           *m_pNextCarriage;
    CDoor             m_aDoors[6];
    RwFrame          *m_aTrainNodes[TRAIN_NUM_NODES];

    static unsigned int& GenTrain_Track;
    static unsigned int& GenTrain_TrainConfig;
    static unsigned char& GenTrain_Direction;
    static unsigned int& GenTrain_GenerationNode;
    static unsigned int& GenTrain_Status;
    static bool& bDisableRandomTrains;

    static CVector *aStationCoors; // { 1741.0, -1954.0, 15.0
                                   //   1297.0, -1898.0, 3.0
                                   //   -1945.0, 128.0, 29.0
                                   //   1434.0, 2632.0, 13.0
                                   //   2783.0, 1758.0, 12.0
                                   //   2865.0, 1281.0, 12.0 }

    CTrain(int modelIndex, unsigned char createdBy);

	bool FindMaximumSpeedToStopAtStations(float* speed);
	unsigned int FindNumCarriagesPulled();
	void OpenTrainDoor(float state); // dummy function
	void AddPassenger(CPed* ped); // dummy function
	void RemovePassenger(CPed* ped); // dummy function
    bool FindSideStationIsOn(); 
    bool IsInTunnel();
    void RemoveRandomPassenger();
    void FindPositionOnTrackFromCoors();
    void AddNearbyPedAsRandomPassenger();

    static void ReadAndInterpretTrackFile(char* filename, CTrainNode** nodes, int* lineCount, float* totalDist, int skipStations);
    static void Shutdown();
    static void UpdateTrains(); // dummy function
    static void FindCoorsFromPositionOnTrack(float railDistance, int trackId, CVector* outCoors); // dummy function
	static void DisableRandomTrains(bool disable);
	static void RemoveOneMissionTrain(CTrain* train);
	static void ReleaseOneMissionTrain(CTrain* train);
	static void SetTrainSpeed(CTrain* train, float speed);
	static void SetTrainCruiseSpeed(CTrain* arg0, float cruiseSpeed);
	static CTrain* FindCaboose(CTrain* train);
	static CTrain* FindEngine(CTrain* train);
	static CTrain* FindCarriage(CTrain* train, unsigned char carriage);
	static void FindNextStationPositionInDirection(bool clockwiseDirection, float distance, float* distanceToStation, int* numStations);
	static void RemoveMissionTrains();
	static void RemoveAllTrains();
	static void ReleaseMissionTrains();
	static int FindClosestTrackNode(CVector posn, int* outTrackId);
	static CTrain* FindNearestTrain(CVector posn, bool mustBeMainTrain);
	static void SetNewTrainPosition(CTrain* train, CVector posn);
	static bool IsNextStationAllowed(CTrain* train);
	static void SkipToNextAllowedStation(CTrain* train);
	static void InitTrains();
	static void CreateMissionTrain(CVector posn, bool clockwiseDirection, unsigned int trainType, CTrain**outFirstCarriage, CTrain**outLastCarriage, int nodeIndex, int trackId, bool isMissionTrain);
	static void DoTrainGenerationAndRemoval();
};

VALIDATE_SIZE(CTrain, 0x6AC);

extern unsigned int *NumTrackNodes; // unsigned int NumTrackNodes[4]
extern CTrainNode **pTrackNodes; // CTrainNode *pTrackNodes[4]
extern float *StationDist; // float StationDist[6]

void ProcessTrainAnnouncements(); // dummy function
void PlayAnnouncement(unsigned char arg0, unsigned char arg1);
void TrainHitStuff(CPtrList& ptrList, CEntity* entity);
void MarkSurroundingEntitiesForCollisionWithTrain(CVector arg0, float arg1, CEntity* arg2, bool arg3);