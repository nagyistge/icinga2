/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012 Icinga Development Team (http://www.icinga.org/)        *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#include "i2-compatido.h"

using namespace icinga;

/**
 * Constructor for the IdoSocket class.
 *
 * @param role The role of the underlying TCP client.
 */
IdoSocket::IdoSocket(TcpClientRole role)
	: TcpClient(role)
{
	/* 
	 * we currently do not receive any data from the ido socket,
	 * this is just data output - so we do not need to bind
	 * a local instance of our datahandler in case of a new 
	 * signal telling about new data
	 */
	OnDataAvailable.connect(boost::bind(&IdoSocket::DataAvailableHandler, this));
}

/**
 * Sends a message to the ido socket
 *
 * @param message The message.
 */
void IdoSocket::SendMessage(const String& message)
{
	/* 
	 * write our message to the send queue
	 * as we inherit all the functionality
	 * of the tcpclient class
	 */
	Write(message.CStr(), message.GetLength());
}

/**
 * Processes inbound data.
 * Currently not used, as we do not receive data from ido sockets
 */
void IdoSocket::DataAvailableHandler(void)
{
	return;
}

/**
 * Factory function for ido socket clients.
 *
 * @param fd The file descriptor.
 * @param role The role of the underlying TCP client.
 * @returns A new ido socket client.
 */
IdoSocket::Ptr icinga::IdoSocketFactory(SOCKET fd, TcpClientRole role)
{
	IdoSocket::Ptr client = boost::make_shared<IdoSocket>(role);
	client->SetFD(fd);
	return client;
}
