#pragma once

//ÉvÉåÉCÉÑÅ[ÇÃPrivateIMPL
class IPlayer::Impl{
public:
	PlayerData playerData;

	int smileFlag;

	const int maxSatiety;
	const int maxExercise;
	const double maxGrouth;
	const double maxTrust;
	const int maxDiseaseCount;
	const int fatCountThresholdS;
	const int fatCountThresholdL;
	const int maxFatCount;

	const double MoveV;
	const int moveTimeMax;
	const int moveTimeMin;

	const double feedGrouth_s;
	const double feedGrouth_m;
	const double feedGrouth_l;
	const double playGrouth_s;
	const double playGrouth_m;
	const double playGrouth_l;
	const double trustRate;
	const double trustThreshold_s;
	const double trustThreshold_l;


	const double moveRate;
	const int fatMoveRate;

	const double mouseSpeedThreshold;

	Circle head;

	Impl(Vector2 h, double r_, int mG);
	Impl(Vector2 h, double r_, int mG, int fTs, int fTl);

	bool reduce_satiety();
	bool reduce_exercise();
	void recover_ill();
	void reset_disease_count();
	void get_thin();
	void reduce_fat_count();
	void set_trust(double x);

	bool increase_satiety(int n);
	bool increase_exercise(int n);
	void increase_grouth(double n);
	bool increase_trust(double x);
	void increase_disease_count();
	void get_ill();
	void increase_fat_count();
	void get_fat();
};