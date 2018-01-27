pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        parallel(
          "Build": {
            sh './setup.sh'
            sh 'rm -rf build && mkdir -p build'
            sh 'cd build && ls -lah'
            sh 'cd build && cmake ..'
            sh 'cd build && ls -lah'
            sh 'cd build && pwd'
            sh 'cd build && make -j 12'
          },
          "Documentation": {
            sh 'doxygen ./doxygen-config'
            sh 'zip -r docs.zip docs'
          }
        )
      }
    }
    stage('Test') {
      steps {
        sh 'cd build && make check'
      }
    }
    stage ('Deploy') {
      when {
        expression { env.BRANCH_NAME == 'master' }
      }
      steps {
        sh "rm -rf ${env.DOCS_WEB_ROOT}/${env.JOB_NAME}/*"
        sh "cp -r ./docs/* ${env.DOCS_WEB_ROOT}/${env.JOB_NAME}"
      }
    }
  }
  post {
    always {
      archive 'docs.zip'
    }
  }
}
