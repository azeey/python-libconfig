# -*- coding: utf-8 -*-

import unittest
import os
try:
    from x86.pylibconfig import Config
except:
    from x64.pylibconfig import Config


class PyLibConfigTest ( unittest.TestCase ):
    def test_greeting ( self ):
        config = Config ()
        
        config.addString ( "", "test" )
        config.setValue ( "test", "value" )

        config.addGroup('','testGrp')
        config.addList('testGrp',"testList")
        config.addArray('testGrp.testList')
        config.appendToList('testGrp.testList.[0]',23.43)
        config.appendToList('testGrp.testList.[0]',3.14)
        config.appendToList('testGrp.testList',3.14)
        config.appendToList('testGrp.testList','3.14')
        config.appendToList('testGrp.testList','pi')
        
        config.addArray('testGrp',"arr1")

        self.assert_ ( config.value ( "test" )[0] == "value" )
        self.assert_ ( config.value ( "test" )[1] == True )
        self.assert_ ( config.value ( "loose" )[1] == False )
        self.assert_ ( config.value ( "testGrp.testList.[0].[0]" )[0] >= 23 )
        self.assert_ ( config.value ( "testGrp.testList.[0].[0]" )[1] == True )
        self.assert_ ( config.value ( "testGrp.testList.[0].[1]" )[0] >= 3 )
        self.assert_ ( config.value ( "testGrp.testList.[0].[1]" )[1] == True )
        self.assert_ ( config.value ( "testGrp.testList.[1]" )[0] >= 3 )
        self.assert_ ( config.value ( "testGrp.testList.[1]" )[1] == True )
        self.assert_ ( config.value ( "testGrp.testList.[2]" )[0] == '3.14' )
        self.assert_ ( config.value ( "testGrp.testList.[2]" )[1] == True )
        self.assert_ ( config.value ( "testGrp.testList.[3]" )[0] == 'pi' )
        self.assert_ ( config.value ( "testGrp.testList.[3]" )[1] == True )
        
        config.writeFile ( "test.conf" )
        
        self.assert_ ( os.path.exists ( "./test.conf" ) == True )
        
        config.readFile ( "test.conf" )

        self.assert_ ( config.value ( "test" )[0] == "value" )
        self.assert_ ( config.value ( "test" )[1] == True )
        self.assert_ ( config.value ( "testGrp.testList.[0].[0]" )[0] >= 23 )
        self.assert_ ( config.value ( "testGrp.testList.[0].[0]" )[1] == True )
        self.assert_ ( config.value ( "testGrp.testList.[0].[1]" )[0] >= 3 )
        self.assert_ ( config.value ( "testGrp.testList.[0].[1]" )[1] == True )
        self.assert_ ( config.value ( "testGrp.testList.[1]" )[0] >= 3 )
        self.assert_ ( config.value ( "testGrp.testList.[1]" )[1] == True )
        self.assert_ ( config.value ( "testGrp.testList.[2]" )[0] == '3.14' )
        self.assert_ ( config.value ( "testGrp.testList.[2]" )[1] == True )
        self.assert_ ( config.value ( "testGrp.testList.[3]" )[0] == 'pi' )
        self.assert_ ( config.value ( "testGrp.testList.[3]" )[1] == True )
        #os.remove ( "./test.conf" )

if __name__ == '__main__':
    unittest.main()
