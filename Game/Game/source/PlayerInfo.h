/*****************************************************************//**
 * \file   PlayerInfo.h
 * \brief  ���L����v���C���[���
 * \author momoka
 * \date   2021 7/9
 *********************************************************************/
#pragma once

class PlayerInfo{
public:
    PlayerInfo();
    virtual ~PlayerInfo();

    void Process();

    //Get�֐�
    int GetFavor() {
        return _favor;
    }
    int GetMolecule() {
        return _molecule;
    }
    int GetCoin() {
        return _coin;
    }
    int GetMentalNum() {
        return _mentalNum;
    }

    //�����֐������֐�
    void SetFavor(int num, bool plus) {
        if (plus) {
            _favor += num;
        }
        else {
            _favor -= num;
        }
    }

    void SetMolecule(int num, bool plus) {
        if (plus) {
            _molecule += num;
        }
        else {
            _molecule -= num;
        }
    }

    void SetCoin(int num, bool plus) {

        if (plus) {
            _coin += num;
        }
        else{
            _coin -= num;
        }
    }

    void SetMentalNum(int num, bool plus) {

        if (plus) {
            _mentalNum += num;
        }
        else {
            _mentalNum -= num;
        }
    }

private:
    int _favor;  //�D���x(num)
    int _molecule;  //�D���x���q(ber)
    int _coin;
    int _mentalNum;  //�ԐF��bar
};