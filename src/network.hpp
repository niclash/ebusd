/*
 * Copyright (C) Roland Jax 2014 <roland.jax@liwest.at>
 *
 * This file is part of ebusd.
 *
 * ebusd is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ebusd is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ebusd. If not, see http://www.gnu.org/licenses/.
 */

#ifndef NETWORK_HPP__
#define NETWORK_HPP__

#include "tcpsocket.hpp"
#include "wqueue.hpp"
#include "thread.hpp"
#include "notify.hpp"
#include <list>

class Connection : public Thread
{

public:
	Connection(TCPSocket* socket) : m_socket(socket), m_running(false) {}
 
	void* run();

	void stop() const { m_notify.notify(); }

	bool isRunning() const { return m_running; }

private:
	TCPSocket* m_socket;
	Notify m_notify;
	bool m_running;

};

class Network : public Thread
{

public:
	Network(int port, std::string ip);
	~Network();
	
	void* run();

	void stop() const { m_notify.notify(); sleep(1); }

private:
	std::list<Connection*> m_connections;
	TCPListener* m_Listener;
	Notify m_notify;
	bool m_listening;
	bool m_running;

	void cleanConnections();

};

#endif // NETWORK_HPP__
