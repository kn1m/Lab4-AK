//
// Created by m3sc4 on 15.12.15.
//

#include <boost/test/unit_test.hpp>
#include <boost/serialization/vector.hpp>
#include <errno.h>
#include "../server_implementation/templates.h"
#include "../server_implementation/thread_implementation.h"
#include "../server_implementation/thread_implementation.h"
#include "../server_implementation/server.h"

#define  BOOST_TEST_DYN_LINK


BOOST_AUTO_TEST_SUITE(test_suite_name)

    BOOST_AUTO_TEST_CASE(connecting) {
        try {
            OutcomingData out("localhost", 8001);
            BOOST_FAIL("Invalid connection didn't throw an exeption.");
        } catch (ConnectionError& sockerr) {
            BOOST_CHECK_EQUAL( sockerr.error_number, ECONNREFUSED );
        }
    }

    BOOST_AUTO_TEST_CASE(comminication) {
        IncomingData in(8000);
        threading::Thread outThread([] (void*)->void* {
            OutcomingData out("localhost", 8000);
            char msg[5] = "test";
            out.writeData(msg, strlen(msg) * sizeof(char));
        });
        auto connection = in.accept_connection();
        char buffer[5];
        memset(buffer, 0, strlen(buffer));
        connection.get()->readData(buffer, 5);
        BOOST_CHECK_EQUAL(string(buffer), string("test"));
    }

BOOST_AUTO_TEST_SUITE_END()