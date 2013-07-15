/*
  * Copyright (C) 2013 Cameron White
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef APP_CARET_H
#define APP_CARET_H

#include <boost/signals2/signal.hpp>
#include <score/scorelocation.h>

/// Tracks the current location within the score.
class Caret
{
public:
    Caret(const Score &score);

    const ScoreLocation &getLocation() const;

    /// Moves the caret left or right by the specified offset.
    void moveHorizontal(int offset);

    /// Moves the caret up or down to the next string, and wraps around
    /// if necessary.
    void moveVertical(int offset);

    /// Moves the caret to the first position in the staff.
    void moveToStartPosition();

    /// Moves the caret to the last position in the staff.
    void moveToEndPosition();

    typedef boost::signals2::signal<void ()> LocationChangedSlot;
    boost::signals2::connection subscribeToChanges(
            const LocationChangedSlot::slot_type &subscriber) const;

private:
    /// Returns the last valid position in the system.
    int getLastPosition() const;

    ScoreLocation myLocation;

    /// Send out signals to subscribers whenever the location changes.
    mutable LocationChangedSlot onLocationChanged;
};

#endif
