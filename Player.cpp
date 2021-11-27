#include "Player.h"

Player* Player::m_players[] = { 0, 0 };
QMutex& Player::m_mutex = *(new QMutex());

Player::Player(Player::Type type)
    : QObject(0), m_type(type),
      m_name(QString("Player %1").arg(type)),
      m_count(0) {
    switch (type) {
        case Player::White:
            m_pixmap = QPixmap(":/white");
            break;
        case Player::Black:
            m_pixmap = QPixmap(":/black");
            break;
        default:
            Q_UNREACHABLE();
            break;
    }
}

Player::~Player() {
}

Player* Player::player(Player::Type type) {
    if (!m_players[type]) {
        QMutexLocker locker(&m_mutex);
        Q_UNUSED(locker);

        if (!m_players[type])
            m_players[type] = new Player(type);
    }

    return m_players[type];
}

Player* Player::other() const {
    switch (m_type) {
        case Player::White:
            return m_players[Player::Black];
        case Player::Black:
            return m_players[Player::White];
        default:
            Q_UNREACHABLE();
            return 0;
    }
}

void Player::inc() {
    m_count++;
    emit countChanged(m_count);
}

void Player::dec() {
    m_count--;
    emit countChanged(m_count);
}
